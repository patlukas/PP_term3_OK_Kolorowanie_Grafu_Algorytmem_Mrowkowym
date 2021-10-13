import random


class Main:
    """
    Klasa służy do tworzenia pliku "instance.txt", który będzie zawierał w pierwszej linii liczbę informującą o ilości
    wierzchołków grafu, a w kolejnych będą umieszczone liczby oddzielone przecinkiem, kolejno:
        - numer krawędzi, numeracja zaczyna się od 1
        - numer wierzchołka o niższym indeksie
        - numer wierzchołka o wyżsym indeksie
    """
    def __init__(self):
        """
        Funkcja odpowiada za stworzenie zmiennych prywatnych w klasie oraz wywołanie metod klasy.
        Zmienne obiektu:
            Prywatne:
                __number_of_vertices - (int) ilość wierzchołków
                __graph_density - (int) gęstość grafu
                __ascending_order - (int) 1 - zwracana lista ma być posortowana rosnąco, 0 - ma być pomieszana
                __edges_list - (list) lista krawędzi grafu
        Wywoływane metody:
            self.__get_data_from_user() - w celu wczytania od użytkownika ewentualnych zmian do zmiennych obeiktu
            self.__generate_list_all_edges() - tworzy w "self.__edges_list" uporzątkowaną listę dostępnych krawędzi
            self.__generate_edges_list() - usuwa losowe elementy z listy "self.__edges_list" aż lista będzie miała
                                           oczekiwaną długość (graf będzie miał odpowiednią gęstość)
            self.__edge_list_blending() - jeżeli zmienna "self.__ascending_order" jest ustawiona na 0 to funkcja
                                          pomiesza listę "self.__edges_list"
            self.__save_edges_list() - funckja zapisuje powstałą listę w pliku "instance.txt"
        """
        self.__number_of_vertices = 30
        self.__graph_density = 50
        self.__ascending_order = 0
        self.__edges_list = []

        self.__get_data_from_user()
        self.__generate_list_all_edges()
        self.__generate_edges_list()
        self.__edge_list_blending()
        self.__save_edges_list()

    def __get_data_from_user(self):
        print("\nWitaj w generatorze instancji do problemu GC!")
        number_of_vertices = input(f"\tIlość wierzchołków w grafie (domyślnie {self.__number_of_vertices}): ")
        graph_density = input(f"\tProcent gęstości grafu (domyślnie {self.__graph_density}%): ")
        ascending_order = input(f"\tCzy wierzchołki mają być ułożone w rosnącej kolejności "
                                f"(1 - Tak, 0 - Nie) (domyślnie {self.__ascending_order}): ")
        try:
            if number_of_vertices != "":
                self.__number_of_vertices = int(number_of_vertices)

            if graph_density != "":
                self.__graph_density = int(graph_density)

            if ascending_order == "1":
                self.__ascending_order = True

        except ValueError:
            print("Error! Któraś z wprowadzonych wartości była błędna")

    def __generate_list_all_edges(self):
        for a in range(1, self.__number_of_vertices):
            for b in range(a+1, self.__number_of_vertices+1):
                self.__edges_list.append([a, b])

    def __generate_edges_list(self):
        maximum_number_of_edges = self.__number_of_vertices * (self.__number_of_vertices - 1) / 2
        while len(self.__edges_list) > maximum_number_of_edges * self.__graph_density / 100:
            index_to_del = random.randint(0, len(self.__edges_list)-1)
            self.__edges_list.pop(index_to_del)

    def __edge_list_blending(self):
        if self.__ascending_order:
            return
        list_after_blending = []
        while len(self.__edges_list):
            index = random.randint(0, len(self.__edges_list)-1)
            list_after_blending.append(self.__edges_list[index])
            self.__edges_list.pop(index)
        self.__edges_list = list_after_blending

    def __save_edges_list(self):
        file = open("instance.txt", "w")
        text = str(self.__number_of_vertices)+"\n"
        for index, [a, b] in enumerate(self.__edges_list):
            text += f"{index+1} {a} {b}\n"
        file.write(text)
        file.close()


if __name__ == "__main__":
    Main()

