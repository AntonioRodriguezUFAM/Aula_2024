## Tutorial Básico de Multithreading em C++

### O que é Multithreading?

Multithreading é uma técnica de programação que permite a execução simultânea de múltiplas sequências de instruções dentro de um mesmo processo. Em outras palavras, um programa pode ter várias "frentes de trabalho" atuando ao mesmo tempo, o que pode levar a um aumento significativo no desempenho, especialmente em sistemas multi-core.

### Por que usar Multithreading em C++?

* **Melhor aproveitamento de hardware:** Em sistemas com múltiplos núcleos de processador, o multithreading permite que tarefas sejam distribuídas por esses núcleos, aumentando a velocidade de execução.
* **Melhora na responsividade:** Tarefas longas ou bloqueadoras podem ser executadas em threads separadas, evitando que a aplicação como um todo fique travada.
* **Modelagem mais natural de problemas:** Em muitos casos, a natureza de um problema se beneficia de uma abordagem paralela.

### Conceitos Básicos

* **Thread:** A menor unidade de execução sequencial dentro de um processo.
* **Processo:** Um programa em execução, com seu próprio espaço de endereço e recursos.
* **Concorrência:** A capacidade de múltiplos threads ou processos executarem aparentemente ao mesmo tempo.
* **Paralelismo:** A execução simultânea de múltiplos threads ou processos em múltiplos núcleos de processador.

### Criando Threads em C++

C++11 introduziu o suporte nativo para multithreading através da biblioteca `<thread>`.

```c++
#include <iostream>
#include <thread>

void tarefa() {
    // Código que será executado pela thread
    for (int i = 0; i < 5; ++i) {
        std::cout << "Olá do mundo da thread!\n";
    }
}

int main() {
    std::thread t(tarefa); // Cria uma nova thread executando a função tarefa

    // Código principal
    for (int i = 0; i < 5; ++i) {
        std::cout << "Olá do mundo principal!\n";
    }

    // Espera a thread terminar antes de continuar
    t.join();

    return 0;
}
```

### Gerenciando Threads

* **`join()`:** Bloqueia a thread atual até que a thread especificada termine.
* **`detach()`:** Desacopla a thread, permitindo que ela continue a execução independentemente da thread principal.
* **`std::this_thread::yield()`:** Ceder voluntariamente o controle do processador para outra thread.

### Sincronização entre Threads

Quando múltiplas threads acessam os mesmos dados, é necessário um mecanismo de sincronização para evitar condições de corrida e garantir a consistência dos dados.

* **Mutex:** Um mecanismo de exclusão mútua que garante que apenas uma thread possa acessar um recurso compartilhado por vez.
* **Condição variável:** Permite que uma thread espere por uma condição específica, sendo notificada por outra thread quando a condição se torna verdadeira.

```c++
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void thread1() {
    // ...
    ready = true;
    cv.notify_one();
}

void thread2() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    // ...
}
```

### Considerações Importantes

* **Custo de criação de threads:** A criação de threads tem um custo associado, portanto, evite criar e destruir threads com muita frequência.
* **Deadlocks:** Ocorrem quando duas ou mais threads estão bloqueadas esperando por um recurso que outra thread possui.
* **Condições de corrida:** Acontecem quando o resultado de uma operação depende da ordem em que as threads são executadas.
* **Escalabilidade:** O multithreading nem sempre leva a um aumento linear no desempenho. É importante analisar o problema e a arquitetura do sistema para determinar se o multithreading é a melhor solução.

### Tópicos Avançados

* **Memória compartilhada:** Técnicas para compartilhar dados entre threads.
* **Threads em tempo real:** Threads com requisitos de tempo de resposta rígidos.
* **Pools de threads:** Um conjunto de threads pré-criadas para reutilizar.
* **Bibliotecas de paralelismo:** Como OpenMP e Intel TBB.

*********************************************************************

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

// Shared data
std::atomic<int> counter(0);
std::mutex mutex;
std::condition_variable cv;

// Thread function
void incrementCounter(int numIterations) {
    for (int i = 0; i < numIterations; ++i) {
        std::unique_lock<std::mutex> lock(mutex);
        counter++;
        cv.notify_all(); // Notify all waiting threads
        lock.unlock();
    }
}

int main() {
    const int numThreads = 4;
    const int numIterationsPerThread = 1000000;

    // Create threads
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter, numIterationsPerThread);
    }

    // Wait for threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final counter value
    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
