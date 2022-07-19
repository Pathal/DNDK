#ifndef DNDK_H
#define DNDK_H

#include <array>
#include <format>
#include <map>
#include <string>
#include <ifaddrs.h>

#include <crow.h>

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QScreen>
#include <QStandardItemModel>
#include <QStatusBar>
#include <QTableView>
#include <QWidget>

#include "game/game_rules.hpp"

const int GRID_DIMENSION = 10;

class DNDK : public QMainWindow {
public:
	DNDK(QWidget *parent = nullptr);
	~DNDK();

	bool initialize();
	void stop();

protected:
	bool StartServer();

	crow::SimpleApp server;
	std::string local_address;
	game_rules game;

	// UI Objects
	QLabel* map_label;
	QLabel* turn_info;
	QGridLayout* map_grid_layout;
	QWidget* map_grid;
	QLabel* grid[GRID_DIMENSION][GRID_DIMENSION];
	std::map<std::string, QImage*> img_lookup;
};
#endif // DNDK_H
