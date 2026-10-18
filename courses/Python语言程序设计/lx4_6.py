class sfz:
    id=None
    def get_year(self):
        birth=self.id[6:10]
        return birth
    def Disp(self):
        print(f"身份证号码是：{self.id}")
if __name__=="__main__":
    people=sfz()
    people.id=input("请输入您的身份证号码：")
    people.Disp()
    print(f"您的出生年份为：{people.get_year()}")
