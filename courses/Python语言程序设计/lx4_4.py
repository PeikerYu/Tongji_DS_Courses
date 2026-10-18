def picture_func(pathway):
    try:
        from PIL import Image
        im=Image.open(pathway)
        im.show()
        im=im.convert("L")
        im=im.point(lambda x:255 if x>140 else 0)
        im=im.convert("1")
        im=im.resize((300,100))
        im.save("sign.jpg")
        im.show()
    except Exception as e:
        print(e)
if __name__=="__main__":
    picture_func(r"signature.jpg")