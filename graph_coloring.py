class Main:
    def __init__(self):
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
        try:
            file = open("instance.txt", "r")
        except FileNotFoundError:
            print("Nie znaleziono pliku 'instance.txt'")
            return
        self.__number_of_vertices = int(file.readline())
        for line in file:
            line = line.replace(f"\r\n", "")
            line = line.replace(f"\n", "")
            list_numbers = line.split()
            a, b = int(list_numbers[1]), int(list_numbers[2])
            if a > b:
                continue
                ## Czy jeżeli a > b to na liście jest również para b a ?
            if a == b:
                print(f"Istnieje krawędź łącząca wierzchołek {a} z samym sobą!")
                continue
            self.__edges_list.append([a, b])

    def __create_empty_vertex_colors_and_empty_incidence_matrix(self):
        for index in range(1, self.__number_of_vertices+1):
            self.__incidence_matrix[index] = []
            self.__vertex_colors[index] = 0

    def __create_incidence_matrix(self):
        for [a, b] in self.__edges_list:
            self.__incidence_matrix[a].append(b)
            self.__incidence_matrix[b].append(a)

    def __assigning_colors(self):
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
