#include"Graph.h"


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");


	glutInit(&argc, argv);

	setGraph();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);//��������� ����� ������� ����� ���������� ������� �� �����
	glutInitWindowSize(WinW, WinH);
	glutCreateWindow("������� ������ ������������");
	glutDisplayFunc(display);//������������ ���������� ������� ��������� ������
	glutReshapeFunc(reshape);//�������� �� ���������������� �����������
	glutMouseFunc(mouseClick);//�������������� � �����

	glutMainLoop();

	return 0;
}