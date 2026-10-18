from PIL import Image
def func2(path):
    s = '@#S%?*+;:,.'
    new_pic=[]
    try:
        img=Image.open(path)
        img=img.convert('L')
        width,height=img.size
        for x in range(width):
            line=''
            for y in range(height):
                p=img.getpixel((x,y))
                p=p//25
                char=s[p%len(s)]
                line+=char
            new_pic.append(line)
        fp=open("tj.txt", "w", encoding="UTF-8")
        fp.write('\n'.join(new_pic))
        print("已保存到tj.txt")
    except Exception as e:
        print(e)

if __name__=="__main__":
    func2("tj.jpg")


