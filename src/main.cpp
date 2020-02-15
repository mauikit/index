#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QCommandLineParser>
#include <QDebug>
#include "index.h"
#include "inx.h"

#include <MauiKit/mauikit.h>

#ifdef Q_OS_ANDROID
#include <QGuiApplication>
#include <QIcon>
#include "mauiandroid.h"
#else
#include <QApplication>
#endif

#ifdef STATIC_KIRIGAMI
#include "3rdparty/kirigami/src/kirigamiplugin.h"
#endif

#ifdef STATIC_MAUIKIT
#include "3rdparty/mauikit/src/mauikit.h"
#endif

Q_DECL_EXPORT int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef Q_OS_ANDROID
    QGuiApplication app(argc, argv);
    if (!MAUIAndroid::checkRunTimePermissions({"android.permission.WRITE_EXTERNAL_STORAGE"}))
        return -1;
#else
	QApplication app(argc, argv);
#endif

    MauiKit::getInstance().initResources();

	app.setApplicationName(INX::appName);
	app.setApplicationVersion(INX::version);
	app.setApplicationDisplayName(INX::displayName);
	app.setOrganizationName(INX::orgName);
	app.setOrganizationDomain(INX::orgDomain);
	app.setWindowIcon(QIcon(":/index.png"));

	QCommandLineParser parser;
	parser.setApplicationDescription(INX::description);
	const QCommandLineOption versionOption = parser.addVersionOption();
	parser.addOption(versionOption);
	parser.process(app);

	const QStringList args = parser.positionalArguments();
	QStringList paths;

	if(!args.isEmpty())
		paths = args;

#ifdef STATIC_KIRIGAMI
	KirigamiPlugin::getInstance().registerTypes();
#endif

#ifdef STATIC_MAUIKIT
	MauiKit::getInstance().registerTypes();
#endif

	Index index;
	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url, paths, &index](QObject *obj, const QUrl &objUrl)
	{
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);

		if(!paths.isEmpty())
			index.openPaths(paths);

	}, Qt::QueuedConnection);

	const auto context = engine.rootContext();
	context->setContextProperty("inx", &index);
	engine.load(url);
	return app.exec();
}
