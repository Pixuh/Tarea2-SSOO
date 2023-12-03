# Tarea2-SSOO
Tarea 2 sistemas operativos

Instrucciones de Instalación para Proyecto Tarea 2 (proyecto creado en ubuntu)
Clonar el Repositorio de github o bajarlo desde moodle
```
git clone https://github.com/Pixuh/Tarea2-SSOO.git 
```
Instalar Dependencias
```
sudo apt-get update
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
```
Configurar y Compilar OpenCV (dentro de la carpeta del proyecto)

Descargar el repositorio de opencv desde github

```
https://github.com/opencv/opencv.git
```
```
cd opencv
mkdir build
cd build
cmake ..
make
```

Configurar y Compilar tu Proyecto

```
cd ../../  # Regresa a la carpeta principal del proyecto
mkdir build
cd build
cmake ..
make
./Tarea2-SSOO
```
Esto debería configurar y compilar tanto OpenCV como tu proyecto correctamente. Recuerda ajustar las rutas y nombres de archivo según corresponda a tu proyecto.

Nota:

    Si deseas mantener OpenCV localmente en tu proyecto, omite sudo make install al compilar OpenCV y ajusta las configuraciones en tu proyecto en consecuencia.
    Asegúrate de tener los permisos necesarios para instalar paquetes con sudo.
