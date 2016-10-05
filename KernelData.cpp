#include "KernalData.h"

#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>

using namespace std;

KernelData::KernelData():_pWtValue(NULL), _size(0){
}

KernelData::~KernelData(){

	if (_pWtValue){
		delete _pWtValue;
		_pWtValue = NULL;

	}
	_size = 0;
}


float KernelData::CalculateScale() {


	if (NULL == _pWtValue) return 0.0f;
	
	//Local variables needed
	float LocalScale = 0.0f;
	int BlockSize = _size*_size;
	float posval = 0.0f, negval = 0.0f;

	for (int i = 0; i < BlockSize; i++){
		
		float nbcurr = _pWtValue[i];
		
		if (0 < nbcurr) {
			posval += nbcurr;
		}
		else{
			negval += nbcurr;
		}

	}

	//Taking input from the homework assignment page:-
	//This should be the maximum magnitude of the sum of the positive weights and the sum of the negative weights
	if (negval == posval) {
		LocalScale = posval;
	}
	else{
		LocalScale = (negval < posval) ? posval : negval;
	}

	return LocalScale;
}

void KernelData::ReadFile(char *ipFileName) {

	FILE *fp = NULL;

	fp = fopen(ipFileName,"r");

	if (NULL == fp)
	{
		cout << "Kernel File was not read" << endl;
		return;
	}

	float scaleInFile;
	fscanf(fp,"%d%f",&_size,&scaleInFile);

	
	if (0 == (_size % 2)) {
		//TODO: invalid kernel size cannot be even

		cout << "invalid kernel. Size cannot be even" << endl;
		return;
	}

	//Size of Kernel array to allocate a _size * _size array of values
	int nbSizeOfKernel = (_size*_size);
	_pWtValue = new float[nbSizeOfKernel];
	
	//Reading the .filt file to store the values in the internal array
	for(int i = 0; i<nbSizeOfKernel ; i++){ 
		
		float tmp = 0.0;
		if (0 != fscanf(fp, "%f", &tmp))
			_pWtValue[i] = tmp;
	}

	//Calculation of scale
	_scale = CalculateScale();
	
	//cout << "scale = " << _scale << endl;

	fclose(fp);

	return;
}


int KernelData::GetHalfSize() {

	return (_size / 2);
}


float KernelData::GetScale() {

	return _scale;
}

int KernelData::GetSize() {

	return _size;
}

float *KernelData::GetWtValue() {

	return _pWtValue;
}

