#include "../darktheme/src/DarkStyle.h"
#include "Theme.h"
#include <QApplication>
#include <QRgb>

// StandardStyle

class StandardStyle : public QProxyStyle {
private:
	LegacyWindowsStyleTreeControl legacy_windows_;
public:
	StandardStyle()
		: QProxyStyle(0)
	{
	}
	void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = 0) const
	{
		if (element == QStyle::PE_IndicatorBranch) {
			if (legacy_windows_.drawPrimitive(element, option, painter, widget)) {
				return;
			}
		}
		QProxyStyle::drawPrimitive(element, option, painter, widget);
	}
};

// AbstractTheme

AbstractTheme::AbstractTheme()
{

}

AbstractTheme::~AbstractTheme()
{

}

// StandardTheme

StandardTheme::StandardTheme()
{
}

QStyle *StandardTheme::newStyle()
{
	return new StandardStyle();
}

QImage StandardTheme::graphColorMap()
{
	QImage image;
	image.load(":/image/graphcolor.png");
	return image;
}

QPixmap StandardTheme::resource_clear_png()
{
	return QPixmap(":/image/clear.png");
}

// DarkTheme

DarkTheme::DarkTheme()
{
}

QStyle *DarkTheme::newStyle()
{
	return new DarkStyle();
}

QImage DarkTheme::graphColorMap()
{
	QImage image;
	image.load(":/darktheme/graphcolor.png");
	return image;
}

QPixmap DarkTheme::resource_clear_png()
{
	QImage img(":/image/clear.png"); // clear.pngは黒画像なので、α値だけ維持して白に変換する
	int w = img.width();
	int h = img.height();
	for (int y = 0; y < h; y++) {
		QRgb *p = (QRgb *)img.scanLine(y);
		for (int x = 0; x < w; x++) {
			int a = qAlpha(*p);
			*p = qRgba(255, 255, 255, a);
			p++;
		}
	}
	return QPixmap::fromImage(img);
}

ThemePtr createStandardTheme()
{
	AbstractTheme *p = new StandardTheme;
	p->text_editor_theme = TextEditorTheme::Light();

	p->diff_slider_normal_bg = Qt::white;
	p->diff_slider_unknown_bg = QColor(208, 208, 208);
	p->diff_slider_add_bg = QColor(64, 192, 64);
	p->diff_slider_del_bg = QColor(240, 64, 64);
	p->diff_slider_handle = Qt::black;

	return ThemePtr(p);
}

ThemePtr createDarkTheme()
{
	AbstractTheme *p = new DarkTheme;
	p->text_editor_theme = TextEditorTheme::Dark();

	p->diff_slider_normal_bg = QColor(48, 48, 48);
	p->diff_slider_unknown_bg = QColor(0, 0, 0);
	p->diff_slider_add_bg = QColor(0, 144, 0);
	p->diff_slider_del_bg = QColor(160, 0, 0);
	p->diff_slider_handle = QColor(255, 255, 255);

	return ThemePtr(p);
}