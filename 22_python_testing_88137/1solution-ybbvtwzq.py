import tkinter as tk
from tkinter import filedialog, ttk
import pandas as pd
import random 
import requests

# Reading all work sheet with pandas
read_file = pd.ExcelFile(r'/home/kai/assignemnet/cherry-bee-inc-2021-data-for-rev-cycle-4-oxnplcsu.xlsx')
read_file_1 = pd.read_excel(read_file, 'tblAccount')
read_file_2 = pd.read_excel(read_file, 'tblCustomer')
read_file_3 = pd.read_excel(read_file, 'tblEmployee')
read_file_4 = pd.read_excel(read_file, 'tblInventory')
read_file_5 = pd.read_excel(read_file, 'tblSale')
read_file_6 = pd.read_excel(read_file, 'tblSale_Inventory')
read_file_7 = pd.read_excel(read_file, 'tblHoneyType')
read_file_8 = pd.read_excel(read_file, 'tblContainerType')
read_file_9 = pd.read_excel(read_file, 'tblContainerSize')
read_file_10 = pd.read_excel(read_file, 'tblState')
read_file_11 = pd.read_excel(read_file, 'tblAcctType')
read_file_12 = pd.read_excel(read_file, 'tblCustomerType')
read_file_13 = pd.read_excel(read_file, 'tblEmployeeType')
read_file_14 = pd.read_excel(read_file, 'tblEmployeePosition')

# Initiating Tkinter GUI
root = tk.Tk()

root.geometry("600x600")    # Dimension
root.pack_propagate(False)  # Not defining the size by default
root.resizable(0, 0)        # Makes the window in a fixed size

# Frame for TreeView
frame1 = tk.LabelFrame(root, text="Data from Excel Sheet")
frame1.place(height=280, width=520)

# Frame for opening dialogue box
file_frame = tk.LabelFrame(root, text="Open a File")
file_frame.place(height=120, width=430, rely=0.65, relx=0)

# Buttons
button1 = tk.Button(file_frame, text="Browse files", command=lambda: File_dialog())
button1.place(rely=0.65, relx=0.50)

button2 = tk.Button(file_frame, text="Load a file", command=lambda: Load_excel_data())
button2.place(rely=0.15, relx=0)

label_file = ttk.Label(file_frame, text="No File Selected")
label_file.place(rely=0, relx=0)


# Treeview widget

tv1 = ttk.Treeview(frame1)
tv1.place(relheight=1, relwidth=1)                                          # Height and weight of widgets

treescrolly = tk.Scrollbar(frame1, orient="vertical", command=tv1.yview)    # y-axis view updates
treescrollx = tk.Scrollbar(frame1, orient="horizontal", command=tv1.xview)  # x-axis view updates

tv1.configure(xscrollcommand=treescrollx.set, yscrollcommand=treescrolly.set)

treescrollx.pack(side="bottom", fill="x")
treescrolly.pack(side="right", fill="y")


def File_dialog():
    filename = filedialog.askopenfilename(initialdir="/",
                                          title="Select A File")
    label_file["text"] = filename
    return None

def Load_excel_data():
    file_path = label_file["text"]
    try:
        excel_filename = r"{}".format(file_path)
        if excel_filename[-4:] == ".csv":
            df = pd.read_csv(excel_filename)
        else:
            df = pd.read_excel(excel_filename)
            
    except ValueError:
        tk.messagebox.showerror("Information", "The file you have chosen is invalid")
        return None
    except FileNotFoundError:
        tk.messagebox.showerror("Information", "No such file as {file_path}")
        return None
    
    clear_data()
    tv1["column"] = list(df.columns)
    tv1["show"] = "headings"
    for column in tv1["columns"]:
        tv1.heading(column, text=column)
    
    df_rows = df.to_numpy().tolist()
    for row in df_rows:
        tv1.insert("", "end", values=row)
    return None

def clear_data():
    tv1.delete(*tv1.get_children())
    return None

def weeklyPaid(hours_worked, wage):
    if hours_worked > 40:
        return 40 * wage + (hours_worked - 40) * wage * 1.5
    else:
        return hours_worked * wage

c = True
while c == True:
    hours_worked = int(input("Enter the number of hours: "))
    wage = 100
    
    pay = weeklyPaid(hours_worked, wage)

    print(f"Total gross pay: Rs.{pay:.2f} ")    # Change it as you wish

root.mainloop()