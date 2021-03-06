#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
//this simple class represents a cut variable used in some selection
//this variable has a name, min value, max value, step size, and
//threshold value between the min and max 

class CutVar {
public:
     CutVar(std::string cutName_, std::string zone, float val, float min, float max, float step, bool setUpper):
	  _cutName(cutName_),
	  _detectorRegion(zone),
	  _threshVal(val),
	  _minThresh(min),
	  _maxThresh(max),
	  _threshStep(step),
	  _isUpperBound(setUpper){
	  };

	 CutVar(std::string cutName_, std::string zone):
	  _cutName(cutName_),
	  _detectorRegion(zone){
	  };

     inline void setThresholdValue(float value){ _threshVal = value;};

     void SetValuesFromString(std::string ranges_){
	  char sign;
	  sscanf(ranges_.c_str(), "[%f,%f,%f,%c]", &_minThresh, &_maxThresh, &_threshStep, &sign);
	  if(sign == '>') _isUpperBound=false;
	  else if(sign == '<') _isUpperBound=true;
	  else exit(1); /// \todo fix launching exception with error 
     }

	 /**use this fxn to check that the minimum, maximum, and step size for a CutVar are assigned reasonable
	  * values, whether the CutVar is identified as an upper bound or lower bound, and the detector region
	  * (EB, tracked EE, etc) in which this CutVar is relevant.
	  * the CutVar name is printed first
	  */
     friend std::ostream& operator << (std::ostream& os, const CutVar a){
	  os <<  a._cutName  << "\t[" << std::setprecision(3) << a._minThresh << "," << a._maxThresh << "," << a._threshStep << ",";
	  char c = a._isUpperBound ? '<' : '>';
	  os << c << "]\t" << a._detectorRegion;
	  return os;
     }

public:
     // _detectorRegion is used to distinguish tracked EB, tracked EE, and trackless EE
     std::string _cutName, _detectorRegion;
     float _threshVal, _minThresh, _maxThresh, _threshStep;
     bool _isUpperBound;	//indicates if this cut will be used as an upper bound (someVal < _threshVal)
};//end class cutVar

