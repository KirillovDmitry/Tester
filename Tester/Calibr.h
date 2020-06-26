// класс, содержащий данные калибровки

class Calibr
{
	public:
	  double get(int);
	  void load();

	static Calibr& getInstance() {
			static Calibr  instance;
			return instance;
		}

	private:
	  Calibr();
	  double CalibrData[128];
};

// функция считывания i-калибровки
double Calibr::get(int i)
{
	return CalibrData[i];
}

Calibr::Calibr()
{
	CalibrData[0] = 0;
	CalibrData[1] = 0;
	CalibrData[2] = 0;
	CalibrData[3] = 0;
	CalibrData[4] = 0;
	CalibrData[5] = 0;
	CalibrData[6] = 0;
	CalibrData[7] = 0;
	CalibrData[8] = 0;
	CalibrData[9] = 0;

	CalibrData[10] = 1;
	CalibrData[11] = 1;
	CalibrData[12] = 1;
	CalibrData[13] = 1;
	CalibrData[14] = 1;
	CalibrData[15] = 1;
	CalibrData[16] = 1;
	CalibrData[17] = 1;
	CalibrData[18] = 1;
	CalibrData[19] = 1;

	CalibrData[20] = 2;
	CalibrData[21] = 2;
	CalibrData[22] = 2;
	CalibrData[23] = 2;
	CalibrData[24] = 2;
	CalibrData[25] = 2;
	CalibrData[26] = 2;
	CalibrData[27] = 2;
	CalibrData[28] = 2;
	CalibrData[29] = 2;

	CalibrData[30] = 3;
	CalibrData[31] = 3;
	CalibrData[32] = 3;
	CalibrData[33] = 3;
	CalibrData[34] = 3;
	CalibrData[35] = 3;
	CalibrData[36] = 3;
	CalibrData[37] = 3;
	CalibrData[38] = 3;
	CalibrData[39] = 3;

	CalibrData[40] = 4;
	CalibrData[41] = 4;
	CalibrData[42] = 4;
	CalibrData[43] = 4;
	CalibrData[44] = 4;
	CalibrData[45] = 4;
	CalibrData[46] = 4;
	CalibrData[47] = 4;
	CalibrData[48] = 4;
	CalibrData[49] = 4;

	CalibrData[50] = 5;
	CalibrData[51] = 5;
	CalibrData[52] = 5;
	CalibrData[53] = 5;
	CalibrData[54] = 5;
	CalibrData[55] = 5;
	CalibrData[56] = 5;
	CalibrData[57] = 5;
	CalibrData[58] = 5;
	CalibrData[59] = 5;

	CalibrData[60] = 6;
	CalibrData[61] = 6;
	CalibrData[62] = 6;
	CalibrData[63] = 6;
	CalibrData[64] = 6;
	CalibrData[65] = 6;
	CalibrData[66] = 6;
	CalibrData[67] = 6;
	CalibrData[68] = 6;
	CalibrData[69] = 6;

	CalibrData[70] = 7;
	CalibrData[71] = 7;
	CalibrData[72] = 7;
	CalibrData[73] = 7;
	CalibrData[74] = 7;
	CalibrData[75] = 7;
	CalibrData[76] = 7;
	CalibrData[77] = 7;
	CalibrData[78] = 7;
	CalibrData[79] = 7;

	CalibrData[80] = 8;
	CalibrData[81] = 8;
	CalibrData[82] = 8;
	CalibrData[83] = 8;
	CalibrData[84] = 8;
	CalibrData[85] = 8;
	CalibrData[86] = 8;
	CalibrData[87] = 8;
	CalibrData[88] = 8;
	CalibrData[89] = 8;

	CalibrData[90] = 9;
	CalibrData[91] = 9;
	CalibrData[92] = 9;
	CalibrData[93] = 9;
	CalibrData[94] = 9;
	CalibrData[95] = 9;
	CalibrData[96] = 9;
	CalibrData[97] = 9;
	CalibrData[98] = 9;
	CalibrData[99] = 9;

	CalibrData[100] = 10;
	CalibrData[101] = 10;
	CalibrData[102] = 10;
	CalibrData[103] = 10;
	CalibrData[104] = 10;
	CalibrData[105] = 10;
	CalibrData[106] = 10;
	CalibrData[107] = 10;
	CalibrData[108] = 10;
	CalibrData[109] = 10;

	CalibrData[110] = 11;
	CalibrData[111] = 11;
	CalibrData[112] = 11;
	CalibrData[113] = 11;
	CalibrData[114] = 11;
	CalibrData[115] = 11;
	CalibrData[116] = 11;
	CalibrData[117] = 11;
	CalibrData[118] = 11;
	CalibrData[119] = 11;

	CalibrData[120] = 12;
	CalibrData[121] = 12;
	CalibrData[122] = 12;
	CalibrData[123] = 12;
	CalibrData[124] = 12;
	CalibrData[125] = 12;
	CalibrData[126] = 12;
	CalibrData[127] = 12;
}

