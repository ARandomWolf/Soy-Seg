#include "QtGuiApplication1.h"
#include <QImage>
#include <string>
#include <qpixmap.h>
#include <iostream>
#include <QFileDialog>
#include "itkImage.h"
#include "itkImageFileReader.h"
#include <itkRGBPixel.h>
#include "itkImageFileWriter.h"
#include "itkMetaImageIOFactory.h"
#include "itkTIFFImageIOFactory.h"
#include "itkTIFFImageIO.h"
#include "itkExtractImageFilter.h"



QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QWidget(parent)
{
	
	ui.setupUi(this);

}

// "load Img" button ??remove?
void QtGuiApplication1::on_loadImg_clicked() {
	ui.tlbl->setText("lol");
	ui.tlbl->setScaledContents(true);
	QPixmap pixmap("C:/Users/wyatt/Documents/capstone/LG05-4464/LG05-4464 rep 1 a.tif");
	fileName = "C:/Users/wyatt/Documents/capstone/LG05-4464/LG05-4464 rep 1 a.tif";
	ui.tlbl->setPixmap(pixmap);
	
}

// "Choose Img" button 
void QtGuiApplication1::on_chooseImg_clicked() {
	 fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"/home",
		tr("Images (*.png *.tiff *.tif *.jpg)"));

	// keeps currently displayed image when no file is selected
	if (fileName != NULL) {
		ui.tlbl->setScaledContents(true);
		QPixmap pixmap(fileName);
		ui.tlbl->setPixmap(pixmap);
	}
}

void QtGuiApplication1::on_processButton_clicked() {
	
	std::string foo = fileName.toUtf8().constData();
	const char * inputFileName = (foo.c_str());
	const char * outputFileName = "C:/Users/wyatt/Pictures/moose.tif";

	typedef itk::RGBPixel<unsigned char> PixelType;
	typedef itk::Image< PixelType, 2 > ImageType ;
	typedef itk::Image<PixelType, 2> ImageOutType;
	typedef  itk::ImageFileReader< ImageType > ReaderType ;
	ReaderType::Pointer reader = ReaderType::New();
	

	reader->SetImageIO(itk::TIFFImageIO::New());
	reader->SetFileName(inputFileName);
	reader->Update();
	
	
	using WriterType = itk::ImageFileWriter< ImageOutType >;
	WriterType::Pointer writer = WriterType::New();

	typedef itk::ExtractImageFilter<ImageType, ImageOutType> FilterType;
	FilterType::Pointer filter = FilterType::New();
	filter->InPlaceOn();
	filter->SetDirectionCollapseToSubmatrix();
	reader->UpdateOutputInformation();
	ImageType::RegionType inputRegion =
		reader->GetOutput()->GetLargestPossibleRegion();	ImageType::SizeType size = inputRegion.GetSize();
	size[2] = 0;
	ImageType::IndexType start = inputRegion.GetIndex();
	const unsigned int sliceNumber = std::stoi("0");
	start[2] = sliceNumber;
	ImageType::RegionType desiredRegion;
	desiredRegion.SetSize(size);
	desiredRegion.SetIndex(start);
	filter->SetExtractionRegion(desiredRegion);
	filter->SetInput(reader->GetOutput());
	writer->SetFileName(outputFileName);
	//writer->Update();




	writer->SetImageIO(itk::TIFFImageIO::New());
	writer->SetInput(filter->GetOutput());
	//writer->SetFileName(outputFileName);
	//writer->SetInput(reader->GetOutput());

	writer->Update();

	ui.tlbl->clear();


}