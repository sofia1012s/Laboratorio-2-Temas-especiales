#Librerias
import serial
import time 
import serial.tools.list_ports

# ---------------- Variables ----------------
data =[]    #Lista para datos de arduino
ports = []  #Lista para puertos COM disponibles
comando = "Datos" + '\n' # Comando para enviar a arduino

# ---------------- Funciones ----------------
# Funcion para buscar puertos seriales y definir uno
def puerto():
    #Buscando puertos seriales
    for port in serial.tools.list_ports.comports():
        ports.append(port.name)
    print("Lista de puertos:")
    for i, item in enumerate(ports,1):
        print(i, '. ' + item, sep='',end='')
        
    #Seleccionando puerto
    input_puerto = input("\nEscriba el número del puerto que desea: ")
    puerto = str(ports[int(input_puerto)-1])
    
    #Conexión serial
    s = serial.Serial(port = puerto,baudrate=115200)
    time.sleep(1) #Al conectar el puerto serial, debemos esperar un tiempo para que empiece la comunicación
    return s
    
    
# Funcion para recibir los datos del puerto serial
def in_puerto(s):
    for i in range(3):              #Queremos temperatura, humedad y si está oscuro o no
        b = s.readline()       # read a byte string
        string_n = b.decode()       # decode byte string into Unicode  
        string = string_n.rstrip()  # remove \n and \r
        flt = float(string)         # convert string to float
        data.append(flt)            # add to the end of data list
        time.sleep(0.1)             # wait (sleep) 0.1 seconds
    
    print (data)
    
def out_puerto(s):
    s.write(string.encode())


# ---------------- Código Main ----------------
puerto_serial = puerto()