#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<glut.h>
#include<string>
#include<iomanip>
#include<algorithm>
using namespace std;


float WinW = 1280.0;
float WinH = 720.0;
float R = 0.0;
const int maxSize = 20;

int amount_vertex, amount_rib, source_vertex, target_vertex, rib_weight;
vector<vector<int>> adj_matrix(maxSize, vector<int>(maxSize));
vector<vector<int>> double_adjM_K;


void drawButton1(); //кнопка для выполнения алгоритма Д
void drawCircle(int x, int y, int R); //круг в заданных координатах
void drawText(int nom, int x1, int y1);	//рисуем вес ребра между 2 вершинами
void drawLine(int text, int x0, int y0, int x1, int y1); //ребро неориентированный взвешенный граф
void drawVertex(int n);	//рисование вершины
void setCoords(int i, int n); //установка координат вершины в завис. от размеров окна
void mouseClick(int button, int state, int x, int y); //отслеживание нажатий
void reshape(int w, int h);	//установка новых размеров окна
void display();


class Graph
{
public:
	Graph();
	~Graph() {}
	bool IsEmpty();
	bool IsFull();
	void InsertVertex(const int& vertex);
	void InsertEdge(const int& vertex1, const int& vertex2, int weight);
	int GetVertPos(const int& vertex);
	void Print();
	int task_Komovoizhora();
	void drawGraph();		//рисование созданного заранее графа

private:
	vector<bool> visit;
	vector<int> min_ways;
	vector<int> vert_list;

};
Graph graph;


struct vertC   //структура координат вершин
{
	int x, y;
};
vertC vC[20];


Graph::Graph()
{
	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < maxSize; j++)
		{
			adj_matrix[i][j] = 0;
		}
	}
}

bool Graph::IsEmpty()
{
	if (vert_list.size() != 0)
		return false;
	else
		return true;
}

bool Graph::IsFull()
{
	return (vert_list.size() == maxSize);
}

void Graph::InsertVertex(const int& vertex)
{
	if (!IsFull())
		vert_list.push_back(vertex);
	else
	{
		cout << "Граф уже заполнен. Невозможно добавить новую вершину " << endl;
		return;
	}
}

int Graph::GetVertPos(const int& vertex)
{
	for (size_t i = 0; i < vert_list.size(); i++)
	{
		if (vert_list[i] == vertex)
			return i;
	}
	return -1;
}



void Graph::InsertEdge(const int& vertex1, const int& vertex2, int weight)
{
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))						//если вершины есть в графе
	{
		int vertPos1 = GetVertPos(vertex1);												//находим позиции вершин
		int vertPos2 = GetVertPos(vertex2);
		if (adj_matrix[vertPos1][vertPos2] != 0 && adj_matrix[vertPos2][vertPos1] != 0)	//если между ними уже есть ребро
		{
			cout << "Ребро между вершинами уже есть" << endl;
			return;
		}
		else																			//иначе добавляем ребро
		{
			adj_matrix[vertPos1][vertPos2] = weight;
			adj_matrix[vertPos2][vertPos1] = weight;
		}
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}

void Graph::Print()
{
	if (!IsEmpty())
	{
		cout << "Матрица смежности графа: " << endl;
		for (size_t i = 0; i < vert_list.size(); i++)
		{
			cout << vert_list[i] << " ";
			for (size_t j = 0; j < vert_list.size(); j++)
				cout << setw(4) << adj_matrix[i][j];
			cout << endl;
		}
	}
	else
		cout << "Граф пуст " << endl;
}

int Graph::task_Komovoizhora()
{
	vector<vector<int>> adjMatrix_Komivoiazhor(amount_vertex, vector<int>(amount_vertex));
	for (int i = 0; i < amount_vertex; i++)
	{
		for (int j = 0; j < amount_vertex; j++)
		{
			if (i == j)
			{
				adjMatrix_Komivoiazhor[i][j] = 999;
			}

			else
				adjMatrix_Komivoiazhor[i][j] = adj_matrix[i][j];
		}
	}

	double_adjM_K = adjMatrix_Komivoiazhor;

	int* di = new int[amount_vertex];
	int min = 0;
	for (int i = 0; i < amount_vertex; i++)
	{
		min = 1000;

		for (int j = 0; j < amount_vertex; j++)
		{
			if (adjMatrix_Komivoiazhor[i][j] < min)
			{
				min = adjMatrix_Komivoiazhor[i][j];
			}
		}
		di[i] = min;
	}
	for (int i = 0; i < amount_vertex; i++)
	{
		for (int j = 0; j < amount_vertex; j++)
		{
			adjMatrix_Komivoiazhor[i][j] -= di[i];
		}
	}

	cout << "С учетом минимумов по строкам:\n";
	for (int i = 0; i < amount_vertex; i++)
	{
		cout << i + 1 << "  ";
		for (int j = 0; j < amount_vertex; j++)
		{
			cout << setw(4) << adjMatrix_Komivoiazhor[i][j];
		}
		cout << endl;
	}
	cout << endl;
	//_____________________________________________________

	//2.Нахождение минимумов по столбцам
	int* dj = new int[amount_vertex];
	int min_ = 0;
	for (int i = 0; i < amount_vertex; i++)
	{
		min_ = 1000;
		for (int j = 0; j < amount_vertex; j++)
		{
			if (adjMatrix_Komivoiazhor[j][i] < min_)
			{
				min_ = adjMatrix_Komivoiazhor[j][i];
			}
		}
		dj[i] = min_;
	}
	for (int i = 0; i < amount_vertex; i++)
	{
		for (int j = 0; j < amount_vertex; j++)
		{
			adjMatrix_Komivoiazhor[j][i] -= dj[i];
		}
	}

	cout << "С учетом минимумов по столбцам:\n";
	for (int i = 0; i < amount_vertex; i++)
	{
		cout << i + 1 << "  ";
		for (int j = 0; j < amount_vertex; j++)
		{
			cout << setw(4) << adjMatrix_Komivoiazhor[i][j];
		}
		cout << endl;
	}
	cout << endl;

	delete[] di;
	delete[] dj;
	//_____________________________________________________

	//3.Вычисление оценок нулевых клеток
	vector<vector<int>> tmp_vector = adjMatrix_Komivoiazhor;

	//находим минимумы по строкам для нулевых клеток
	int* di_ = new int[amount_vertex];
	int min_not_null_Str = 0;
	for (int i = 0; i < amount_vertex; i++)
	{
		//выясняем сколько нулей с строке
		int counter = 0;
		min_not_null_Str = 1000;
		for (int j = 0; j < amount_vertex; j++)
		{
			if (tmp_vector[i][j] == 0) counter++;
		}

		//находим минимум
		for (int z = 0; z < amount_vertex; z++)
		{
			if (counter < 2)
			{
				if (tmp_vector[i][z] != 0 && tmp_vector[i][z] < min_not_null_Str)
					min_not_null_Str = tmp_vector[i][z];
			}
			else
				min_not_null_Str = 0;
		}
		di_[i] = min_not_null_Str;
	}


	//находим минимум по столбцам для нулевых клеток
	int* dj_ = new int[amount_vertex];
	int min_not_null_Stl = 0;
	for (int i = 0; i < amount_vertex; i++)
	{
		//выясняем сколько нулей в столбце
		int counter = 0;
		min_not_null_Stl = 1000;
		for (int j = 0; j < amount_vertex; j++)
		{
			if (tmp_vector[j][i] == 0) counter++;
		}

		//находим минимум
		for (int z = 0; z < amount_vertex; z++)
		{
			if (counter < 2)
			{
				if (tmp_vector[z][i] != 0 && tmp_vector[z][i] < min_not_null_Stl)
					min_not_null_Stl = tmp_vector[z][i];
			}
			else
				min_not_null_Stl = 0;
		}
		dj_[i] = min_not_null_Stl;
	}


	//вместо нулей подставляем сумму минимумов по строке и столбцу
	for (int i = 0; i < amount_vertex; i++)
	{
		for (int j = 0; j < amount_vertex; j++)
		{
			if (tmp_vector[i][j] == 0)
			{
				tmp_vector[i][j] = di_[i] + dj_[j];
			}
		}
	}

	cout << "С учетом оценок нулевых значений:\n";
	for (int i = 0; i < amount_vertex; i++)
	{
		cout << i + 1 << "  ";
		for (int j = 0; j < amount_vertex; j++)
		{
			cout << setw(4) << tmp_vector[i][j];
		}
		cout << endl;
	}
	cout << endl;

	delete[] di_;
	delete[] dj_;

	//4.Ищем максимумальную из нулевых клеток
	vector<vector<int>> Result(amount_vertex, vector<int>(amount_vertex));
	for (int i = 0; i < amount_vertex; i++)
	{
		for (int j = 0; j < amount_vertex; j++)
		{
			Result[i][j] = 0;
		}
	}

	//теперь сравниваем найденно маскимальное нулевое значение с tmp_vector чтобы каким путям принадлежит данное значение 
	int global_exit = 0;
	int global_i = -1;
	int global_j = -1;
	while (global_exit != amount_vertex)
	{
		int max_null = 0;
		for (int i = 0; i < amount_vertex; i++)
		{
			if (i != global_i)
			{
				for (int j = 0; j < amount_vertex; j++)
				{
					if (j != global_j)
					{
						if (tmp_vector[i][j] < 500 && adjMatrix_Komivoiazhor[i][j] == 0)
						{
							if (tmp_vector[i][j] > max_null)
								max_null = tmp_vector[i][j];
						}
					}
				}
			}
		}

		for (int i = 0; i < amount_vertex; i++)
		{
			if (i != global_i)
			{
				for (int j = 0; j < amount_vertex; j++)
				{
					if (j != global_j)
					{
						if (tmp_vector[i][j] == max_null && adjMatrix_Komivoiazhor[i][j] == 0)
						{
							Result[i][j] = max_null;
							tmp_vector[j][i] = 999;
							global_i = i;
							global_j = j;
							global_exit++;
						}
					}
				}
			}
		}
	}


	cout << "Итоговая редукция матрицы:\n";
	int one = 0;
	for (int i = 0; i < amount_vertex; i++)
	{
		cout << i + 1;
		for (int j = 0; j < amount_vertex; j++)
		{
			cout << setw(4) << Result[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Минимальный путь с посещением всех вершин:\n";
	int summ = 0;
	int id = 0;
	vector<int> mass_count;
	for (int i = 0; i < amount_vertex; i++)
	{
		for (int j = 0; j < amount_vertex; j++)
		{
			if (Result[i][j])
			{
				cout << i + 1 << "->" << j + 1 << "->";
				mass_count.push_back(i);
				id++;
				mass_count.push_back(j);
				id++;
			}
		}
	}
	one = mass_count[0];
	mass_count.push_back(one);
	cout << one + 1 << " = ";



	for (int i = 0; i < id; i++)
	{
		summ += double_adjM_K[mass_count[i]][mass_count[i + 1]];
	}
	cout << summ << ".";

	return 0;
}

void drawButton1() //кнопка для выполнения алгоритма Д
{
	glColor3f(0.902f, 0.902f, 0.980f);

	glBegin(GL_QUADS);
	glVertex2i(0, WinH);
	glVertex2i(0, WinH - WinH / 6);
	glVertex2i(WinW / 6, WinH - WinH / 6);
	glVertex2i(WinW / 6, WinH);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2i(0, WinH);
	glVertex2i(0, WinH - WinH / 6);
	glVertex2i(WinW / 6, WinH - WinH / 6);
	glVertex2i(WinW / 6, WinH);
	glEnd();

	string but1 = "Zadacha ";
	string but2 = " Komivoiazhora ";
	glRasterPos2i(4, WinH - 12);
	for (int i = 0; i < but1.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, but1[i]);
	glRasterPos2i(4, WinH - 32);
	for (int i = 0; i < but2.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, but2[i]);
}

void drawCircle(int x, int y, int R) //круг в заданных координатах
{
	glColor3f(0.9f, 0.9f, 0.9f);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(int nom, int x1, int y1)	//рисуем вес ребра между 2 вершинами
{
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(nom);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (size_t j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void drawLine(int text, int x0, int y0, int x1, int y1) //ребро неориентированный взвешенный граф
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();

	drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);
}


void drawVertex(int n)	//рисование вершины
{
	for (int i = 0; i < n; i++)
	{
		drawCircle(vC[i].x, vC[i].y, R);
		drawText(i + 1, vC[i].x, vC[i].y);
	}
}

void setCoords(int i, int n) //установка координат вершины в завис. от размеров окна
{
	int R_;
	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10;
	}
	else
	{
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10;
	}
	float theta = 2.0f * 3.1415926f * i / n;
	int y1 = R_ * cos(theta) + y0;
	int x1 = R_ * sin(theta) + x0;

	vC[i].x = x1;
	vC[i].y = y1;
}

void Graph::drawGraph()	//рисование созданного заранее графа
{

	int n = vert_list.size();
	for (int i = 0; i < n; i++)
	{
		setCoords(i, n);	//установка координат
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int a = adj_matrix[i][j];
			if (a != 0)
			{
				drawLine(a, vC[i].x, vC[i].y, vC[j].x, vC[j].y);		//ребро
			}
		}
	}
	drawVertex(n);		//вершина
}

void mouseClick(int button, int state, int x, int y) //отслеживание нажатий
{
	if (x <= (WinW / 6) and y <= (WinH / 6)) //1 кнопка
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			int k = graph.task_Komovoizhora();
			if (k == -1)
				cout << "error";
		}
}

void setGraph()	//создание графа
{

	cout << "Введите количество вершин графа: "; cin >> amount_vertex; cout << endl;
	cout << "Введите количество ребер графа: "; cin >> amount_rib; cout << endl;
	for (int i = 1; i <= amount_vertex; i++) {

		int* vertPtr = &i;
		graph.InsertVertex(*vertPtr);
	}
	for (int i = 0; i < amount_rib; i++)
	{
		cout << "Исходная вершина: "; cin >> source_vertex; cout << endl;
		int* source_vertPtr = &source_vertex;
		cout << "Конечная вершина: "; cin >> target_vertex; cout << endl;
		int* target_vertPtr = &target_vertex;
		cout << "Вес ребра: "; cin >> rib_weight; cout << endl;
		graph.InsertEdge(*source_vertPtr, *target_vertPtr, rib_weight);
	}
	cout << endl;
	graph.Print();
}

void reshape(int w, int h)	//установка новых размеров окна
{
	WinW = w;
	WinH = h;

	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void display()
{
	glMatrixMode(GL_PROJECTION);	//установка новой сис. координат
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawButton1();
	graph.drawGraph();

	glutSwapBuffers();
}



