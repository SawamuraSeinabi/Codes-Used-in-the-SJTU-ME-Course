'''类'''

class people():
    def __init__(self,name = 'Jack',age = 16):
        self.name = name
        self.age = age

        self.country = 'Chine'

    def introduce(self,):
        s = 'My name is %s'%self.name
        print(s)
P1 = people(name ='RBQT',age = 24)
P1.introduce()

class people_Asian(people):
    def __init__(self):
        super(people,self),__init__()
        self.hobby = 'basketball'

'''
car
属性：车牌号 车型 剩余寿命 音乐list
方法：翻新（refresh） 添加音乐（add_music）
同时print
'''

class car():
    def __init__(self,platenum,model,life,musiclist):
        self.platenum = platenum
        self.model = model
        self.life = life
        self.musiclist = musiclist
    def carcar(self,):
        print('This is a car whose number is %s'%self.platenum +
              '.And it is a %s'%self.model +
              '.It has worked for some time and it still has a lifetime for %s'%self.life)
    def refresh(self,life):
        self.life += life
    def add_music(self,musiclist):
        