class Main:
    def __init__(self):
        """
        Zmienne obiektu:
            __number_of_vertices (int) liczba wierzchołków
            __edges_list (list) lista dwuelementowych list w których wartości oznaczają między jakimi
                                                           wierzchołkami jest krawędź
            __incidence_matrix (dict) lista incydencji, czyli każdy wierzchołek ma swój klucz gdzie jest lista intów
                                      z którymi jest połączony,
                                      istnieje zarówno pod kluczem a wartość b jak pod kluczem b wartość a
            __vertex_colors (dict) słownik gdzie każdy wierzchołek ma miejsce do wpisania koloru, początkowo wszystkie
                                   wierzchołki mają kolor 0, ale ostatecznie to musi się zmienić, bo kolory
                                   będą liczbami całkowitymi dodatkimi
        """
        self.__number_of_vertices = 0
        self.__edges_list = []
        self.__incidence_matrix = {}
        self.__vertex_colors = {}

        self.__loading_a_list_of_edges()
        self.__create_empty_vertex_colors_and_empty_incidence_matrix()
        self.__create_incidence_matrix()

        self.__assigning_colors()

        print(self.__incidence_matrix)
        print(self.__vertex_colors)

    def __loading_a_list_of_edges(self):
        """
        Funckja odpowiada za wczytanie danych z pliku "instance.txt".
        Kończy działanie jeżeli nie udało się znaleźć/otworzyć pliku.
        Przed odczytywaniem wartości z linii, funkcja usuwa znak enteru z pobrnej linii.
        Z pierwszej linii odczytuje ilość wierzchołków,
        a z kolejnych numer krawędzi, pierwszy wierzchołek i drugi wierzchołek.
        Jeżeli nie uda się zamienić jakiejś wartości na int to zwraca błąd.
        Jeżeli w drugiej i kolejnych liniach funkcja nie wykryje 3 liczb to zwraca ostrzeżenie i pomija linię.
        Jeżeli pierwsza cyfra jest większa od drugiej to zwraca ostrzeżenie i pomija linię.
        Jeżeli pierwsza cyfra jest równa drugiej to zwraca ostrzeżenie i pomija linię.
        Jeżeli wszystko było okej z linią to dodaje numery wierzchołkó do listy krawędzi
        """
        try:
            file = open("instance.txt", "r")
        except FileNotFoundError:
            print("Nie znaleziono pliku 'instance.txt'")
            return

        try:
            nr_line = 1
            self.__number_of_vertices = int(file.readline())
            for line in file:
                nr_line += 1
                line = line.replace(f"\r\n", "")
                line = line.replace(f"\n", "")
                list_numbers = line.split()
                if len(list_numbers) != 3:
                    print(f'W pliku "instance.txt" w linii {nr_line} nie są trzy liczby')
                    continue
                a, b = int(list_numbers[1]), int(list_numbers[2])
                if a > b:  # Czy jeżeli a > b to na liście jest również para b a ?
                    continue
                if a == b:
                    print(f"Istnieje krawędź łącząca wierzchołek {a} z samym sobą!")
                    continue
                self.__edges_list.append([a, b])
        except ValueError:
            print(f'W pliku "instance.txt" w linii {nr_line} nie są tylko liczby')
            return

    def __create_empty_vertex_colors_and_empty_incidence_matrix(self):
        """
        Funckja tworzy dla każdego wierzchołka pustą listę w tablicy incydencji oraz ustawia kolor wierzchołka na 0
        :return:
        """
        for index in range(1, self.__number_of_vertices+1):
            self.__incidence_matrix[index] = []
            self.__vertex_colors[index] = 0

    def __create_incidence_matrix(self):
        """
        Funkcja uzupełnia w słowniku "self.__incidence_matrix"  listy pod indeksem "a" że sąsiaduje on z "b",
        a "b" że sąsiaduje z "a"
        """
        for [a, b] in self.__edges_list:
            self.__incidence_matrix[a].append(b)
            self.__incidence_matrix[b].append(a)

    def __assigning_colors(self):
        """
        Funkcja przechodzi po kolei po wierzchołkach grafu.
        Przy każdym wierzchołku tworzy listę "list_used_colors" którą uzupełnia numerami kolorów które zostały użyte
        w sąsiadach tego wierzchołka (domyślnie jeżeli wierzchołek nie ma przypisanego koloru to ma wartość 0).
        Następnie szuka najmniejszej liczby całkowitej dodatniej, która nie jest na liście użytych kolorów
        """
        for vertex in self.__vertex_colors.keys():
            list_used_colors = []
            for second_vertex in self.__incidence_matrix[vertex]:
                list_used_colors.append(self.__vertex_colors[second_vertex])
            for color in range(1, self.__number_of_vertices+1):
                if color not in list_used_colors:
                    self.__vertex_colors[vertex] = color
                    break


if __name__ == "__main__":
    Main()
