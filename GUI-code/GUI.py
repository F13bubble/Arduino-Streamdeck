import serial
import tkinter as tk
from tkinter import ttk
import json
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
print(dir_path)
PORT = 'COM3'
BAUD = 9600
CONFIG_FILE = "\\streamdeck_config.json"

ACTIONS = {
    "Copy (Ctrl+C)": 1,
    "Paste (Ctrl+V)": 2,
    "Cut (Ctrl+X)": 3,
    "Lock Screen (Win+L)": 4,
    "Task Manager": 5,
    "Open Chrome": 6,
    "Open Notepad": 7,
    "Open Visual Studio Code": 8,
    "Open cmd": 9,
    "Homescreen": 10,
    "Screenshot": 11,
    "Play/Pause": 12,
    "Next Track": 13,
    "Previous Track": 14,
    "Mute": 21,
    "PowerToys Color Picker": 15,
    "PowerToys Text Extractor": 16,
    "PowerToys Screen Ruler": 17,
    "PowerToys Always On Top": 18,
    "Git Push (not supported)": 19,
    "Git Pull (not suppotred)": 20,
    # "test": 0,
    # "test": 0,
    "Custom Key: Enter": 100 + 13,
}


# === load JSON ===
def load_config():
    if os.path.exists(dir_path + CONFIG_FILE):
        try:
            with open(dir_path + CONFIG_FILE, 'r') as f:
                return json.load(f)
        except Exception as e:
            print("Failed to load json:", e)
    return {}

# === save JSON ===
def save_config(config):
    with open(dir_path + CONFIG_FILE, 'w') as f:
        json.dump(config, f, indent=4)

# === send mapping ===
def send_mapping():
    config = {}
    try:
        ser = serial.Serial(PORT, BAUD, timeout=1)
        for i in range(12):
            action_label = dropdown_vars[i].get()
            action_id = ACTIONS.get(action_label)
            if action_id is None:
                print(f"⚠️ Invalid action for key {i}: {action_label}")
                continue
            command = f"{i}:{action_id}\n"
            ser.write(command.encode())
            print(f"Sende: {command.strip()}")
            config[str(i)] = action_label
        ser.close()
        save_config(config)
        print("✅ Configuration saved.")
    except Exception as e:
        print("❌ Error sending:", e)

# === GUI ===
root = tk.Tk()
root.title("Streamdeck - Key assignment")
root.geometry("600x600")

dropdowns = []
dropdown_vars = []
config_data = load_config()

for i in range(12):
    frame = ttk.Frame(root)
    frame.pack(pady=5)
    ttk.Label(frame, text=f"Key {i}").pack(side='left', padx=5)

    var = tk.StringVar()
    dropdown_vars.append(var)
    
    combo = ttk.Combobox(frame, textvariable=var)
    combo['values'] = list(ACTIONS.keys())

    saved_value = config_data.get(str(i))
    if saved_value in ACTIONS:
        var.set(saved_value)
    else:
        var.set("")

    combo.pack(side='left')
    dropdowns.append(combo)

ttk.Button(root, text="Send", command=send_mapping).pack(pady=10)
root.mainloop()
