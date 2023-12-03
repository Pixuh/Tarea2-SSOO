#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

void aplicarFiltroLuminosidad(cv::Mat &imagen) {
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < imagen.rows; ++i) {
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

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time =
        std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    std::cout << "Tiempo de ejecucion:" << elapsed_time << " segundos\n";
}

int main() {
    cv::Mat imagen = cv::imread("/Tarea2-SSOO/src/auto.jpg");

    if (imagen.empty()) {
        std::cerr << "No se pudo cargar la imagen." << std::endl;
        return 1;
    }

    aplicarFiltroLuminosidad(imagen);

    cv::imwrite("imagen_procesada_secuencial.jpg", imagen);

    std::cout << "Proceso completado. Imagen guardada como 'imagen_procesada_secuencial.jpg'"
              << std::endl;

    return 0;
}
