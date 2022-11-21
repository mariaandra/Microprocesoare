from tkinter import *

window = Tk()
window.title('VibrationBuzzerLed')

window.geometry("400x200")
window.minsize(400, 200)
window.maxsize(400, 200)

label = Label(window, text='COM')
insert = Entry(window)
label.grid(row=0, column=0)
insert.grid(row=0, column=1)
label.place(relx = 0.25,rely = 0.5,anchor='center')
insert.place(relx = 0.5,rely = 0.5,anchor='center')

window.mainloop()
