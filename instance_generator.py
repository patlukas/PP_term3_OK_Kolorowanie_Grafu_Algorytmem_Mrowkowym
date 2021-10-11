import random
import time


class Main:
    def __init__(self):
        self.__number_of_vertices = 10
        self.__graph_density = 50
        self.__edges_list = []

        self.__get_data_from_user()
        self.__generate_list_all_edges()
        self.__generate_edges_list()
        self.__save_edges_list()

    def __get_data_from_user(self):
        print("Witaj w generatorze instancji do problemu GC!\n")
        number_of_vertices = input(f"Ilość wierzchołków w grafie (domyślnie {self.__number_of_vertices}): ")
        graph_density = input(f"Procent gęstości grafu (domyślnie {self.__graph_density}%): ")

        if number_of_vertices != "":
            self.__number_of_vertices = int(number_of_vertices)

        if graph_density != "":
            self.__graph_density = int(graph_density)

    def __generate_list_all_edges(self):
        for a in range(self.__number_of_vertices):
            for b in range(a+1, self.__number_of_vertices+1):
                self.__edges_list.append([a, b])

    def __generate_edges_list(self):
        maximum_number_of_edges = self.__number_of_vertices * (self.__number_of_vertices - 1) / 2
        while len(self.__edges_list) - 1 > maximum_number_of_edges * self.__graph_density / 100:
            index_to_del = random.randint(0, len(self.__edges_list))
            self.__edges_list.pop(index_to_del)

    def __save_edges_list(self):
        file = open("instance.txt", "w")
        text = str(self.__number_of_vertices)+"\n"
        for index, [a, b] in enumerate(self.__edges_list):
            text += f"{index+1} {a} {b}\n"
        file.write(text)
        file.close()


if __name__ == "__main__":
    Main()

