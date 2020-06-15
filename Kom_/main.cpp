#include"Graph.h"


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");


	glutInit(&argc, argv);

	setGraph();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);//указываем каким образом будут выводиться объекты на экран
	glutInitWindowSize(WinW, WinH);
	glutCreateWindow("Решение задачи Коммивояжера");
	glutDisplayFunc(display);//регистрируем дисплейную функцию обратного вызова
	glutReshapeFunc(reshape);//отвечает за масштабируемость изображения
	glutMouseFunc(mouseClick);//взаимодействие с мышью

	glutMainLoop();

	return 0;
}