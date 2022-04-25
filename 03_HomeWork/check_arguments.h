#pragma once

enum class GameType {
	UnknownType = 0,
	SimpleGame = 1,
	WithMaxNumber = 2,
	WithLevel = 3,
	OnlyTable = 4
};

// Функция проверяет корректность переданных аргументов.
bool check_arguments(int args_number, const char** arguments);

// Функция определяет вид игры.
GameType get_game_type(int args_number, const char** arguments, int& second_value);