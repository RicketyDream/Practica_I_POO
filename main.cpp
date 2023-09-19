#include <iostream>
#include <cstdlib>

class EventoTemporal {
public:
    EventoTemporal* PtrPasado;
    EventoTemporal* PtrFuturo;
    std::string evento;
    std::string cientifico;
    int datos;

    EventoTemporal(EventoTemporal* pasado, EventoTemporal* futuro, std::string evento, std::string cientifico, int datos)
            : PtrPasado(pasado), PtrFuturo(futuro), evento(evento), cientifico(cientifico), datos(datos) {}

    bool esEventoA() {
        return evento == "A" && datos > 1 && esPrimo(datos);
    }

    bool esEventoB() {
        return evento == "B" && datos > 1 && esPrimo(datos);
    }

    bool esEventoC() {
        return evento == "C";
    }

    bool esPrimo(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
};

void imprimirLista(EventoTemporal* inicio) {
    EventoTemporal* actual = inicio;
    int contadorA = 0;
    int contadorB = 0;
    while (actual != nullptr) {
        std::cout << "Se ha presentado un evento de tipo: " << actual->evento << std::endl;
        std::cout << " " << actual->datos << " | " << actual->cientifico << " | " << actual->evento << std::endl;
        std::cout << " #" << actual->datos << std::endl;

        if (actual->esEventoA()) {
            contadorA++;
        } else if (actual->esEventoB()) {
            contadorB++;
        }

        actual = actual->PtrFuturo;
    }
    std::cout << std::endl;
    std::cout << "Eventos tipo A: " << contadorA << std::endl;
    std::cout << "Eventos tipo B: " << contadorB << std::endl;
}

int main() {
    srand(time(0));
    EventoTemporal* inicio = nullptr;
    EventoTemporal* anterior = nullptr;

    int tamanoLista = rand() % 20 + 3; // Tamaño mínimo de 3 nodos, máximo de 22 nodos
    for (int i = 0; i < tamanoLista; ++i) {
        std::string evento;
        std::string cientifico;
        int datos = rand() % 100 + 1;
        int cientificoId = rand() % 2 + 1;
        if (cientificoId == 1) {
            cientifico = "Einstein";
        } else {
            cientifico = "Rosen";
        }
        if (anterior == nullptr) {
            evento = "A";
        } else {
            if (anterior->esEventoA()) {
                evento = "B";
            } else if (anterior->esEventoB()) {
                if (rand() % 2 == 0) {
                    evento = "C";
                } else {
                    evento = "B";
                }
            } else {
                evento = "A";
            }
        }
        EventoTemporal* nuevoEvento = new EventoTemporal(anterior, nullptr, evento, cientifico, datos);
        if (anterior != nullptr) {
            anterior->PtrFuturo = nuevoEvento;
        }
        anterior = nuevoEvento;
        if (inicio == nullptr) {
            inicio = nuevoEvento;
        }

        // Imprimir eventos en cada iteración
        imprimirLista(inicio);
    }

    // Liberar memoria de los nodos
    EventoTemporal* actual = inicio;
    while (actual != nullptr) {
        EventoTemporal* siguiente = actual->PtrFuturo;
        delete actual;
        actual = siguiente;
    }

    return 0;
}
