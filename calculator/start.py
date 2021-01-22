#!/usr/bin/python3

from __future__ import division
import tkinter as tk
import tkinter.messagebox as msg
import keyboard

class Calc:
    main = tk.Tk()
    main.geometry("200x200")
    main.title("Calculator")
    txt_expression = ""

    def __init__(self):
        self.uiMenu()
        self.uiButtons()
        self.uiKeyboards()
        self.main.mainloop()

    def aboutMenu(self):
        msg.showinfo("About", "Python Calculator v0.1")

    def uiMenu(self):
        m = tk.Menu(self.main)

        fm = tk.Menu(m, tearoff=0)
        fm.add_command(label="New", command=self.clear)
        fm.add_separator()
        fm.add_command(label="Exit", command=self.main.quit)
        m.add_cascade(label="File", menu=fm)

        am = tk.Menu(m, tearoff=0)
        am.add_command(label="About...", command=self.aboutMenu)
        m.add_cascade(label="Help", menu=am)

        self.main.config(menu=m)

    def uiButtons(self):
        f1 = tk.Frame(self.main)
        f1.pack()

        f2 = tk.Frame(self.main)
        f2.pack()

        f3 = tk.Frame(self.main)
        f3.pack()

        f4 = tk.Frame(self.main)
        f4.pack()

        f5 = tk.Frame(self.main)
        f5.pack()

        tk.Button(f1, text="7", command=lambda: self.clickButton(7),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f1, text="8", command=lambda: self.clickButton(8),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f1, text="9", command=lambda: self.clickButton(9),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)

        tk.Button(f2, text="4", command=lambda: self.clickButton(4),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f2, text="5", command=lambda: self.clickButton(5),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f2, text="6", command=lambda: self.clickButton(6),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)

        tk.Button(f3, text="1", command=lambda: self.clickButton(1),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f3, text="2", command=lambda: self.clickButton(2),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f3, text="3", command=lambda: self.clickButton(3),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)

        tk.Button(f4, text="0", command=lambda: self.clickButton(0),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f4, text=".", command=lambda: self.clickButton("."),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f4, text="=", command=lambda: self.evalExpression(),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)

        tk.Button(f1, text="+", command=lambda: self.clickButton("+"),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f2, text="-", command=lambda: self.clickButton("-"),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f3, text="*", command=lambda: self.clickButton("*"),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)
        tk.Button(f4, text="/", command=lambda: self.clickButton("/"),
                       width=1).pack(side=tk.LEFT, padx=5, pady=5)

    def uiKeyboards(self):
        keyboard.add_hotkey('esc', self.clear)
        keyboard.add_hotkey('1', lambda: self.clickButton(1))
        keyboard.add_hotkey('2', lambda: self.clickButton(2))
        keyboard.add_hotkey('3', lambda: self.clickButton(3))
        keyboard.add_hotkey('4', lambda: self.clickButton(4))
        keyboard.add_hotkey('5', lambda: self.clickButton(5))
        keyboard.add_hotkey('6', lambda: self.clickButton(6))
        keyboard.add_hotkey('7', lambda: self.clickButton(7))
        keyboard.add_hotkey('8', lambda: self.clickButton(8))
        keyboard.add_hotkey('9', lambda: self.clickButton(9))
        keyboard.add_hotkey('0', lambda: self.clickButton(0))
        keyboard.add_hotkey('.', lambda: self.clickButton("."))
        keyboard.add_hotkey(',', lambda: self.clickButton("."))
        keyboard.add_hotkey('+', lambda: self.clickButton("+"))
        keyboard.add_hotkey('-', lambda: self.clickButton("-"))
        keyboard.add_hotkey('*', lambda: self.clickButton("*"))
        keyboard.add_hotkey('/', lambda: self.clickButton("/"))
        keyboard.add_hotkey('=', lambda: self.evalExpression())
        keyboard.add_hotkey('enter', lambda: self.evalExpression())
        keyboard.add_hotkey('backspace', lambda: self.backspace())

    def clear(self):
        self.txt_expression = ""
        self.display.set(self.txt_expression)

    def backspace(self):
        self.txt_expression = self.txt_expression[:-1]
        self.display.set(self.txt_expression)

    def clickButton(self, val):
        self.txt_expression = self.txt_expression + str(val)
        self.display.set(self.txt_expression)

    def evalExpression(self):
        try:
            self.txt_expression = str(eval(self.txt_expression))
        except:
            self.txt_expression = ""
        self.display.set(self.txt_expression)

    display = tk.StringVar()

    e1 = tk.Entry(main, bd=1, textvariable=display)
    e1.pack(side=tk.TOP)

Calc()
