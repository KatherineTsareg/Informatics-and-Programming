#include <SFML/Graphics.hpp>
using namespace sf;

View view;//�������� sfml ������ "���", ������� � �������� �������

void getplayercoordinateforview(float x, float y) { //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
}
