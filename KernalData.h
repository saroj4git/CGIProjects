

class KernelData {

private:
	float *_pWtValue;
	int _size;    //This denotes the array size i.e. [_size] x [_size] array of Weights
	float _scale;
public:
	KernelData();
	~KernelData();

	void ReadFile(char *ipFileName);
	float CalculateScale();
	int GetHalfSize();
	int GetSize();
	float *GetWtValue();
	float GetScale();

};