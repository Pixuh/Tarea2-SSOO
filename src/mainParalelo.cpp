#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <chrono>

void aplicarFiltroLuminosidad(cv::Mat &imagen, int inicio, int fin) {
    for (int i = inicio; i < fin; ++i) {
        for (int j = 0; j < imagen.cols; ++j) {
            int canalAzul = imagen.at<cv::Vec3b>(i, j)[0];
            int canalVerde = imagen.at<cv::Vec3b>(i, j)[1];
            int canalRojo = imagen.at<cv::Vec3b>(i, j)[2];

            int valorLuminosidad = (canalAzul + canalVerde + canalRojo) / 3;

            imagen.at<cv::Vec3b>(i, j)[0] = valorLuminosidad;
            imagen.at<cv::Vec3b>(i, j)[1] = valorLuminosidad;
            imagen.at<cv::Vec3b>(i, j)[2] = valorLuminosidad;
        }
    }
}

void aplicarFiltroLuminosidadParalelo(cv::Mat &imagen) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int num_hilos = std::thread::hardware_concurrency();
    std::vector<std::thread> hilos;

    int seccion = imagen.rows / num_hilos;
    int inicio = 0;
    int fin = seccion;

    for (int i = 0; i < num_hilos; ++i) {
        hilos.emplace_back(aplicarFiltroLuminosidad, std::ref(imagen), inicio, fin);
        inicio = fin;
        fin += seccion;
    }

    for (auto &hilo : hilos) {
        hilo.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time =
        std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    std::cout << "Tiempo de ejecucion: " << elapsed_time << " segundos\n";
}

int main() {
    cv::Mat imagen = cv::imread("/Tarea2-SSOO/src/auto.jpg");

    if (imagen.empty()) {
        std::cerr << "No se pudo cargar la imagen." << std::endl;
        return 1;
    }

    aplicarFiltroLuminosidadParalelo(imagen);

    cv::imwrite("imagen_procesada_paralelo.jpg", imagen);

    std::cout << "Proceso completado. Imagen guardada como 'imagen_procesada_paralelo.jpg'"
              << std::endl;

    return 0;
}

