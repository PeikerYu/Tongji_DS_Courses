"""Wrap the original GIF in responsive SVG banners with readable vector titles."""

from base64 import b64encode
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
GIF_DATA = b64encode((ROOT / "assets/gojo-avant.gif").read_bytes()).decode("ascii")
FONT = "'Microsoft YaHei', 'PingFang SC', 'Noto Sans CJK SC', sans-serif"
TITLE = "🎓 同济大学 数据科学与大数据技术专业课程资料"
ENGLISH = "Tongji University - Data Science and Big Data Technology Courses"


def banner(width: int, height: int, mobile: bool = False) -> str:
    if mobile:
        lines = [
            (330, 30, 700, "🎓 同济大学"),
            (376, 30, 700, "数据科学与大数据技术专业课程资料"),
            (421, 19, 500, "Tongji University"),
            (451, 19, 500, "Data Science and Big Data Technology Courses"),
        ]
        image = f'<image y="-60" width="{width}" height="{height}" preserveAspectRatio="xMidYMid slice" xlink:href="data:image/gif;base64,{GIF_DATA}"/>'
    else:
        lines = [
            (284, 34, 700, "🎓 同济大学"),
            (340, 44, 700, "数据科学与大数据技术专业课程资料"),
            (386, 24, 500, ENGLISH),
        ]
        image = f'<image width="{width}" height="{height}" preserveAspectRatio="xMidYMax slice" xlink:href="data:image/gif;base64,{GIF_DATA}"/>'

    texts = "\n".join(
        f'<text x="{width / 2:g}" y="{y}" font-size="{size}" font-weight="{weight}">{text}</text>'
        for y, size, weight, text in lines
    )
    return f'''<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="{width}" height="{height}" viewBox="0 0 {width} {height}" role="img" aria-labelledby="banner-title banner-description">
  <title id="banner-title">{TITLE}</title>
  <desc id="banner-description">{ENGLISH}。五条悟的蓝色出场动画作为背景，半透明深色渐变承托标题。</desc>
  <defs>
    <clipPath id="corners"><rect width="{width}" height="{height}" rx="16"/></clipPath>
    <linearGradient id="shade" x1="0" y1="0" x2="0" y2="1">
      <stop offset="0" stop-color="#061322" stop-opacity="0.10"/>
      <stop offset="0.40" stop-color="#061322" stop-opacity="0.12"/>
      <stop offset="0.64" stop-color="#061322" stop-opacity="0.70"/>
      <stop offset="1" stop-color="#061322" stop-opacity="0.96"/>
    </linearGradient>
  </defs>
  <g clip-path="url(#corners)">
    <rect width="{width}" height="{height}" fill="#061322"/>
    {image}
    <rect width="{width}" height="{height}" fill="url(#shade)"/>
    <g fill="#f0f9ff" font-family="{FONT}" text-anchor="middle">
      {texts}
    </g>
    <rect x="0.5" y="0.5" width="{width - 1}" height="{height - 1}" rx="15.5" fill="none" stroke="#7dd3fc" stroke-opacity="0.20"/>
  </g>
</svg>
'''


for name, width, height, mobile in [
    ("course-banner.svg", 1200, 440, False),
    ("course-banner-mobile.svg", 600, 500, True),
]:
    path = ROOT / "assets" / name
    path.write_text(banner(width, height, mobile), encoding="utf-8", newline="\n")
    print(f"Built {name}: {width} x {height}, {path.stat().st_size:,} bytes")
