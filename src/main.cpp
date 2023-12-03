#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <opencv2/opencv.hpp>

std::mutex mutex;

void aplicarFiltroLuminosidad(cv::Mat& imagen, int inicio, int fin) {
    for (int i = inicio; i < fin; ++i) {
        for (int j = 0; j < imagen.cols; ++j) {
            int canalAzul, canalVerde, canalRojo;

            {
                std::lock_guard<std::mutex> lock(mutex);
                canalAzul = imagen.at<cv::Vec3b>(i, j)[0];
                canalVerde = imagen.at<cv::Vec3b>(i, j)[1];
                canalRojo = imagen.at<cv::Vec3b>(i, j)[2];
            }

            int valorLuminosidad = (canalAzul + canalVerde + canalRojo) / 3;
            {
                std::lock_guard<std::mutex> lock(mutex);  // Exclusión mutua para acceso a la matriz
                imagen.at<cv::Vec3b>(i, j)[0] = valorLuminosidad;
                imagen.at<cv::Vec3b>(i, j)[1] = valorLuminosidad;
                imagen.at<cv::Vec3b>(i, j)[2] = valorLuminosidad;
            }
        }
    }
}

int main() {
    cv::Mat imagen = cv::imread("tu_imagen.jpg");

    if (imagen.empty()) {
        std::cerr << "No se pudo cargar la imagen." << std::endl;
        return 1;
    }

    int altura = imagen.rows;
    int numHilos = std::thread::hardware_concurrency();
    std::vector<std::thread> hilos;

    int seccion = altura / numHilos;
    int inicio = 0;
    int fin = seccion;

    for (int i = 0; i < numHilos; ++i) {
        hilos.emplace_back(aplicarFiltroLuminosidad, std::ref(imagen), inicio, fin);
        inicio = fin;
        fin += seccion;
    }

    for (auto& hilo : hilos) {
        hilo.join();
    }

    cv::imwrite("imagen_procesada.jpg", imagen);

    std::cout << "Proceso completado. Imagen guardada como 'imagen_procesada.jpg'" << std::endl;

    return 0;
}

