import tkinter as tk
from tkinter import ttk
from tkinter import *
import serial
import serial.tools.list_ports
from PyQt5.QtSerialPort import QSerialPortInfo
import requests
import mysql.connector
import datetime



class Oscilloscope:
    def __init__(self, root):
        self.root = root
        self.root.geometry('800x700+1+1')
        self.root.title('Attendance')
        self.root.configure(background='#e0e0e0')
        self.mystr = tk.StringVar()
        # Create Combobox
        self.com = ttk.Combobox(self.root, state='readonly')
        self.com.place(x=10, y=30)
        
        # Create Buttons
        self.connect_button = tk.Button(self.root, text='Connect', command=self.connect_to_port, fg='black', bg='#9e9e9e', width='15', height='1')
        self.connect_button.place(x=100, y=100)
        self.disconnect_button = tk.Button(self.root, text='Disconnect', command=self.disconnect_port, fg='black', bg='#9e9e9e', width='15', height='1')
        self.disconnect_button.place(x=350, y=100)
        self.Check_button = tk.Button(self.root, text='Check', command=self.read_data, fg='black', bg='#9e9e9e', width='15', height='1')
        self.Check_button.place(x=350, y=160)

        # Create a treeview widget
        self.tree = ttk.Treeview(self.root, columns=("Column 1", "Column 2", "Column 3", "Column 4"), show="headings")

        # Define columns
        self.tree.heading("#1", text="ID")
        self.tree.heading("#2", text="Name")
        self.tree.heading("#3", text="Date Of Create")
        self.tree.heading("#4", text="Date Of Attendance")

        # Insert sample data (you can replace this with your data)

        # Place the treeview widget in your window
        self.tree.place(x=10, y=200)
        # Create Label
        self.connected_label = tk.Label(self.root, text='Connected', fg='black', bg='#e0e0e0', font=10)
        self.connected_label.place(x=170, y=28)

        # Call Refresh_fun initially
        self.Refresh_fun()
        add_button = tk.Button(root, text="Add New Record", command=self.add_record, fg='black', bg='#9e9e9e', width='15', height='1')
        add_button.place(x=650, y=500)
        #add_button.pack()
        # Refresh Button
        Refresh = tk.Button(self.root, command=self.Refresh_fun, text='Refresh', fg='black', bg='#9e9e9e', width='15', height='1')
        Refresh.place(x=600, y=100)

        # Serial Connection Instance
        self.serial_connection = None


    def add_record(self):
        def insert_data():
            # Get data from entry fields
            id_value = id_entry.get()
            name_value = name_entry.get()

            # Get current timestamp
            current_time = datetime.datetime.now()

            # Insert new record into the database
            try:
                conn = mysql.connector.connect(
                    host="localhost",
                    user="root",
                    password="",
                    database="ci_project"
                )

                if conn.is_connected():
                    print("Connected to MySQL database")

                    cursor = conn.cursor()
                    # Prepared statement to fetch row by ID
                    insert_query = "INSERT INTO students (std_id, std_name, date) VALUES (%s, %s, %s)"
                    data = (id_value, name_value, current_time)
                    cursor.execute(insert_query, data)
                    conn.commit()
                    cursor.close()
                    conn.close()
                    print("Connection closed")

            except mysql.connector.Error as e:
                print("Error connecting to MySQL:", e)

            # Close the entry window after adding the record
            entry_window.destroy()

        # Create a new window for data entry
        entry_window = tk.Toplevel(root)
        entry_window.title("Add New Record")
        entry_window.geometry('300x200')
        # Entry fields for ID and Name
        tk.Label(entry_window, text="Student ID").pack()
        id_entry = tk.Entry(entry_window,width=50)
        id_entry.pack()

        tk.Label(entry_window, text="Student Name").pack()
        name_entry = tk.Entry(entry_window,width=50)
        name_entry.pack()

        # Button to submit data
        tk.Button(entry_window, text="Submit", command=insert_data).pack()

    def Refresh_fun(self):
        ports = QSerialPortInfo().availablePorts()
        port_names = [port.portName() for port in ports]
        self.com['values'] = port_names
        
    def connect_to_port(self):
        selected_port = self.com.get()
        if selected_port and not self.serial_connection:
            try:
                # Establish serial connection with custom settings
                self.serial_connection = serial.Serial(
                    port=selected_port,
                    baudrate=1200,  # Set your desired baud rate
                    bytesize=serial.EIGHTBITS,  # Set the data bits (typically 8 bits)
                    parity=serial.PARITY_NONE,  # Set parity (none, odd, even, mark, space)
                    stopbits=serial.STOPBITS_ONE  # Set stop bits (1, 1.5, 2)
                )
                # Use 'serial_connection' for communication with the connected device
                print(f"Connected to port {selected_port} with custom settings")
                self.connected_label.config(fg='red')  # Change label color to red

            except serial.SerialException as e:
                print(f"Failed to connect to port {selected_port}: {e}")

    def disconnect_port(self):
        if self.serial_connection:
            try:
                self.serial_connection.close()  # Close the serial connection
                self.serial_connection = None  # Reset the serial connection object
                print("Disconnected from the port")
                self.connected_label.config(fg='white')  # Change label color to default (white)
            except serial.SerialException as e:
                print(f"Error while disconnecting: {e}")

    def send_data(self,num):
        if self.serial_connection:
            if (num == 1):
                try:
                    # Send data through the serial connection
                    self.serial_connection.write(b'1')  # Send encoded data
                    print("Sent_1")
                except serial.SerialException as e:
                    print(f"Error while sending data: {e}")
            else:
                try:
                    # Send data through the serial connection
                    self.serial_connection.write(b'0')  # Send encoded data
                    print("Sent_0")
                except serial.SerialException as e:
                    print(f"Error while sending data: {e}")

    def get_row_by_id(self,id_value):
        try:
            conn = mysql.connector.connect(
                host="localhost",
                user="root",
                password="",
                database="ci_project"
            )

            if conn.is_connected():
                print("Connected to MySQL database")

                cursor = conn.cursor()
                # Prepared statement to fetch row by ID
                query = "SELECT * FROM students WHERE std_id = %s"
                cursor.execute(query, (id_value,))
                row = cursor.fetchone()
                current_time = datetime.datetime.now()
                row = row + (current_time,)
                # Fetch the first row
                if row:
                    print("Row:", row)
                    self.tree.insert("", tk.END, values=row)
                    self.send_data(1)
                else:
                    print("No matching row found")
                    self.send_data(0)

                cursor.close()
                conn.close()
                print("Connection closed")

        except mysql.connector.Error as e:
            print("Error connecting to MySQL:", e)

    def read_data(self):
        if self.serial_connection and self.serial_connection.is_open:
            data = self.serial_connection.read_all()
            print(f"Raw data: {data}")
            search_value_str = data.decode('latin-1')
            cleaned_data = search_value_str[1:-1]
            self.get_row_by_id(cleaned_data)

if __name__ == "__main__":
    root = tk.Tk()
    oscilloscope_app = Oscilloscope(root)
    root.mainloop()
