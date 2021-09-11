import tkinter
from tkinter import *
boxes= []

refs =[]
#create the main window
root = Tk()
root.geometry("800x800")
root.configure(bg='white')


x = Label(root, anchor = CENTER, text = "                           ", bg= 'white')
x.grid(row=1, column=1)
total_rows = 6
total_columns = 7

#create table
i = 0
x = 0
for i in range(total_rows):
    currentrow = []
    x = i
    for j in range(total_columns):
        e = Entry(root, width=4, fg='black')
        e.grid(row = i + 10, column=j+10)
        info = e.grid_info()
        currentrow.append((info["row"], info["column"]))

    
# create function and button to print the coordinates of each data field       
def solve():
    for r in currentrow:
        print(currentrow)
  
Solve = Button(root, anchor = S, command = solve)
Solve.grid(row = 100, column = 7)


root.mainloop
