import tkinter as tk #GUI library
from tkinter import messagebox
import signal
import sys

def show_ms():
    messagebox.showinfo("Message", "Hola")

# Ventana principal
root = tk.Tk()  # tk.Tk() crea la ventana principal y es asignado a Tk
root.title("Recuadro")
root.geometry("200x100")
root.overrideredirect(True)

# Marco flotante
frame = tk.Frame(root, bg="lightblue", width=200, height=100) #Crea el frame
frame.pack_propagate(False) #Evita que cambie de tamaño
frame.pack() # Coloca el marco en la ventana principal

# Crear un botón en el marco
button = tk.Button(frame, text= "Click", command=show_ms) # {frame, texto, comando} se puede jugar con esto
button.pack(expand=True) #Hace que se expanda para llenar el espacio 

def start_move(event):
    root.x = event.x #event es el cursor parece
    root.y = event.y

def stop_move(event):
    #event unusefull now
    root.x = None
    root.y = None

def do_move(event):
    x = (event.x_root - root.x)
    y = (event.y_root - root.y)
    root.geometry(f"+{x}+{y}")

#bind llama segun el evento
frame.bind("<ButtonPress-1>", start_move) #Refiere al click izquierdo apretado
frame.bind("<ButtonRelease-1>", stop_move) #Refiere al click izquierdo suelto
frame.bind("<B1-Motion>", do_move) #Refiere al click izquierdo en movimiento

#Para controlar el main loop
def signal_handler(sig,frame):
    print("Interrumpir")
    root.destroy()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

root.mainloop() #Hace el bucle para que este atento 