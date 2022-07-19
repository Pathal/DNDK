#include "dndk.h"

DNDK::DNDK(QWidget *parent) : QMainWindow(parent) {
	QScreen* screen = QApplication::primaryScreen();
	resize(screen->availableGeometry().size() * 0.9);

	map_label = new QLabel("Game Map: ", this);
	map_label->setStyleSheet("QLabel{font-size: 20px;}");
	map_label->setGeometry(10,10,200,20);

	turn_info = new QLabel("Current turn: ", this);
	turn_info->setStyleSheet("QLabel{font-size: 20px;}");
	turn_info->setGeometry(700,10,200,20);

	map_grid = new QWidget(this);
	map_grid_layout = new QGridLayout(map_grid);
	map_grid->setLayout(map_grid_layout);
	map_grid->setGeometry(50, 10, 700, 700);

	for(int i = 0; i < GRID_DIMENSION; i++) {
		for(int j = 0; j < GRID_DIMENSION; j++) {
			std::string t = "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
			QString s = t.c_str();
			QLabel* q = new QLabel(s, map_grid);
			q->setGeometry(10+i*20, 10+j*20, 40, 40);
			map_grid_layout->addWidget(q);
		}
	}

	setWindowTitle( QApplication::translate("nestedlayouts", "Nested layouts") );
	setStatusBar(new QStatusBar(this));

	CROW_ROUTE(server, "/")([](){
		return "Hello world";
	});
}

DNDK::~DNDK() {
	//
}

bool DNDK::initialize() {
	StartServer();

	return true;
}

void DNDK::stop() {
	//
}

bool DNDK::StartServer() {
	std::array ports = {80, 8080, 18080};
	int using_port = 0;
	for (auto p : ports) {
		try {
			auto res = server.port(p).multithreaded().run_async();
			using_port = p;
			std::cout << "Server using port: " << p << "\n";
			break;
		} catch(const std::exception& e) {
			std::cout << "Unable to start on port: " + std::to_string(p) + "\n";
			statusBar()->showMessage("Error starting the server. Game is unresponsive.");
		}
	}

	// get the local IP address
	std::vector<std::string> addrs;
#if defined(__APPLE__) || defined(__LINUX__)
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in *sa;
	char *addr;
	getifaddrs(&ifap);
	for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
			sa = (struct sockaddr_in *) ifa->ifa_addr;
			addr = inet_ntoa(sa->sin_addr);
			addrs.emplace_back(addr);
			printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
		}
	}
	freeifaddrs(ifap);
#else
	// TODO other platforms!
#endif

	local_address = addrs[addrs.size()-1] + ":"+std::to_string(using_port);
	std::string connection_string("Server online. Connect to " + local_address);
	statusBar()->showMessage(QString::fromStdString(connection_string));
	return using_port > 0;
}
