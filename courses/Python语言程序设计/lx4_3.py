def show_func(picture_path):
    from PIL import Image
    try:
        im=Image.open(picture_path)
        im.show()
        width, height = im.size
        format = im.format
        mode = im.mode
        print(f"宽度是：{width}\n高度是：{height}\n格式是：{format}\n模式是：{mode}")
        for x in range(width):
            for y in range(int(height/2),height):
                p=im.getpixel((x,y))
                r,g,b=p
                mod=int(0.299*r+0.587*g+0.114*b)
                color=(mod,mod,mod)
                im.putpixel((x,y),color)
        im.save("于沛可.jpg")
        im.show()
    except Exception as e:
        print(f"图片操作异常: {e}")
if __name__=="__main__":
    show_func(r"2451951.jpg")

