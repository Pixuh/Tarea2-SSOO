#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

void aplicarFiltroLuminosidadSecuencial(cv::Mat& imagen) {
    for (int i = 0; i < imagen.rows; ++i) {
        for (int j = 0; j < imagen.cols; ++j) {
            // Obtener los valores de los canales RGB
            int canalAzul = imagen.at<cv::Vec3b>(i, j)[0];
            int canalVerde = imagen.at<cv::Vec3b>(i, j)[1];
            int canalRojo = imagen.at<cv::Vec3b>(i, j)[2];

            // Calcular el valor de luminosidad (escala de grises)
            int valorLuminosidad = (canalAzul + canalVerde + canalRojo) / 3;

            // Establecer el mismo valor en los tres canales para escala de grises
            imagen.at<cv::Vec3b>(i, j)[0] = valorLuminosidad;
            imagen.at<cv::Vec3b>(i, j)[1] = valorLuminosidad;
            imagen.at<cv::Vec3b>(i, j)[2] = valorLuminosidad;
        }
    }
}

void aplicarFiltroLuminosidadThreaded(cv::Mat& imagen, int inicio, int fin) {
    for (int i = inicio; i < fin; ++i) {
        for (int j = 0; j < imagen.cols; ++j) {
            // Obtener los valores de los canales RGB
            int canalAzul = imagen.at<cv::Vec3b>(i, j)[0];
            int canalVerde = imagen.at<cv::Vec3b>(i, j)[1];
            int canalRojo = imagen.at<cv::Vec3b>(i, j)[2];

            // Calcular el valor de luminosidad (escala de grises)
            int valorLuminosidad = (canalAzul + canalVerde + canalRojo) / 3;

            // Establecer el mismo valor en los tres canales para escala de grises
            imagen.at<cv::Vec3b>(i, j)[0] = valorLuminosidad;
            imagen.at<cv::Vec3b>(i, j)[1] = valorLuminosidad;
            imagen.at<cv::Vec3b>(i, j)[2] = valorLuminosidad;
        }
    }
}

int main() {
    // Cargar la imagen
    cv::Mat imagen = cv::imread("src/auto.jpg");

    if (imagen.empty()) {
        std::cerr << "No se pudo cargar la imagen." << std::endl;
        return 1;
    }

    // Versión secuencial
    aplicarFiltroLuminosidadSecuencial(imagen);

    // Guardar la imagen procesada
    cv::imwrite("imagen_procesada_secuencial.jpg", imagen);

    std::cout << "Proceso secuencial completado. Imagen guardada como 'imagen_procesada_secuencial.jpg'" << std::endl;

    // Versión paralela con std::thread
    cv::Mat imagenThreaded = cv::imread("src/auto.jpg");

    if (imagenThreaded.empty()) {
        std::cerr << "No se pudo cargar la imagen para la versión paralela." << std::endl;
        return 1;
    }

    // Número de hilos (puedes ajustar esto según el número de núcleos de tu CPU)
    int numHilos = std::thread::hardware_concurrency();
    std::vector<std::thread> hilos;

    // Dividir la imagen en secciones para cada hilo
    int seccion = imagenThreaded.rows / numHilos;
    int inicio = 0;
    int fin = seccion;

    // Iniciar los hilos
    for (int i = 0; i < numHilos; ++i) {
        hilos.emplace_back(aplicarFiltroLuminosidadThreaded, std::ref(imagenThreaded), inicio, fin);
        inicio = fin;
        fin += seccion;
    }

    // Esperar a que todos los hilos terminen
    for (auto& hilo : hilos) {
        hilo.join();
    }

    // Guardar la imagen procesada
    cv::imwrite("imagen_procesada_threaded.jpg", imagenThreaded);

    std::cout << "Proceso paralelo con std::thread completado. Imagen guardada como 'imagen_procesada_threaded.jpg'" << std::endl;

    return 0;
}

