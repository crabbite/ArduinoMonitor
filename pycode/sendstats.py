import serial
import psutil
import time
import keyboard

# WICHTIG: Ersetze 'COM3' durch deinen Port aus der Arduino IDE (unten rechts)
PORT = 'COM11'
BAUD = 9600
mode = 1
letzte_sendung = 0
uepressed = False


try:
    arduino = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)  # Warte auf Arduino Reset
    print(f"Verbindung zu {PORT} hergestellt.")
except:
    print(f"Fehler: Konnte {PORT} nicht öffnen. Port richtig?")
    exit()
def sende_daten():
        # Diese Funktion holt die Daten und schickt sie sofort raus
        global letzte_sendung
        cpu = int(psutil.cpu_percent())
        cpufreq = int(psutil.cpu_freq().current)
        ram = int(psutil.virtual_memory().percent)
        diskusage = int(psutil.disk_usage('/').percent)

        data = f"#{mode},{cpu},{cpufreq},{ram},{diskusage}\n"
        arduino.write(data.encode('utf-8'))
        letzte_sendung = time.time()
while True:
    time.sleep(0.1)
    jetzt = time.time()
    if(keyboard.is_pressed('ü') ):
        if(not uepressed):
            mode = 1 if (mode == 2) else 2
            sende_daten()
            uepressed = True
    else:
        uepressed = False
    # 1. Daten auslesen
    if(jetzt-letzte_sendung >= 1):
        sende_daten()

