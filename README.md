# Semana 1
Comienza PPS el 17/03/22. Dentro de los objetivos a corto plazo se tiene la utilización de los variadores disponibles en el laboratorio, el uso del analizador de calidad de energía, el diagnóstico y puesta en marcha de un Plotter ENCAD ENJET 4. Los objetivos a largo plazo son la medición y adquisición de tensiones y corrientes transitorias, la documentación de los resultados obtenidos durante la realización de la pasantía y proponer nuevas actividades de laboratorio.

Las pruebas que se realizaron en el plotter indican que la correa principal del carro está dañada, no existe repuesto de la misma. Los variadores disponibles son dos, uno es de la marca ABB modelo SAMI MS y otro es de la marca Schneider modelo Altivar 312. El analizador de calidad de energía es un Metrel MI 2092. No hay documentación online disponible del variador ABB, solo una fotocopia de un manual.

# Semana 2
Reconocimiento de los insumos y herramientas disponibles en el laboratorio. En cuanto a herramientas e instrumentos específicos para electrónica se encuentra un osciloscopio BK Precision 1590A, un generador de funciones, un soldador con temperatura ajustable, fuente de alimentación ajustable y una fuente de alimentación simétrica. Se identificaron los contactores disponibles, muchos de ellos son antiguos y se desconoce la vida útil restante, mientras que los nuevos, en caja, no pueden ser utilizados por falta de transformadores de 24V. Entre la variedad de elementos de maniobra y señalización se observa la ausencia de indicadores tipo ojo de buey de 22mm.

Se identificaron los motores que podrían ser utilizados con variador de frecuencia electrónico ABB Sami MS y Schneider Altivar 312. Lectura sobre arranque de motores y control de velocidad en el libro "Máquinas Eléctricas - Theodore Wildi". Fabricación de bobina Rogowski y posterior prueba con carga resistiva monofásica.

# Semana 3
Arranque de motor asincrónico con contactor, uso del analizador de calidad de energía Metrel MI 2092, conexión a PC del analizador. Se analizó la posibilidad de medir la corriente de arranque del motor con el instrumento, la tasa de actualización mínima es de 1 segundo y las pinzas de corriente disponibles no son adecuadas para medir corrientes pequeñas.
Se propone la reutilización de un banco de trabajo con tableros adecuados para:
  * Arranque directo con contactor, incluir guardamotor de 0.9A a 1.25A. Además de aprender a cablear un contactor, se puede realizar la medición de la corriente a torque nominal y ajustar el guardamotor para proteger al motor.
  * Freno de corriente continua, introducción al principio de frenado con aplicación de corriente continua a uno de los devanados del motor.
  * Uso de variador, rampas de aceleración, torque de arranque máximo.

Cableado y puesta en marcha del variador SAMI, armado de un nuevo panel de comando externo, no fue posible realizar comunicación con la PC mediante RS485 ya que no se dispone de la información ni software necesario para dicha tarea. Este variador puede ser utilizado para que los alumnos realicen las conexiones necesarias, caractericen la curva RPM vs Frecuencia del motor utilizando un tacómetro y verifiquen la respuesta lineal entre la frecuencia y el voltaje del variador. Se podría configurar la salida analógica 4-20mA (terminales 14 y 15) del variador para indicar la corriente de salida (Grupo de parámetros 02, opción 4) y con un amperímetro registar la corriente, de esta manera se podría realizar una curva corriente vs RPM del motor.

# Semana 4
Comunicación por protocolo MODBUS con el variador Altivar 312, instalación y uso del software SoMove. Este variador puede ser utilizado para que los alumnos se familiaricen con la adquisición de datos y la configuración de variadores modernos utilizando un bus de campo.

Implementación, en computadora personal, de DokuWiki, un servicio web para la gestión de documentación de los resultados obtenidos.

Comienza investigación para la implementación de un módulo de adquisición de tensiones y corrientes trifásicas. Entre las características principales se propone:
  * Uso de microcontrolador de bajo costo (ESP8266, ESP32, Arduino Uno, Raspberry Pico)
  * Aislación galvánica
  * Estampas de tiempo al inicio y fin de la medición
  * Alimentación a batería
  * Almacenamiento en tarjeta SD