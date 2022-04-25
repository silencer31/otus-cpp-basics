#pragma once

enum class GameType {
	UnknownType = 0,
	SimpleGame = 1,
	WithMaxNumber = 2,
	WithLevel = 3,
	OnlyTable = 4
};

// ������� ��������� ������������ ���������� ����������.
bool check_arguments(int args_number, const char** arguments);

// ������� ���������� ��� ����.
GameType get_game_type(int args_number, const char** arguments, int& second_value);