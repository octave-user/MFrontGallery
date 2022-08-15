/*!
* \file   TFEL/Material/ChemicalReaction5dBehaviourData.hxx
* \brief  this file implements the ChemicalReaction5dBehaviourData class.
*         File generated by tfel version 4.1.0-dev
* \author Thomas Helfer
* \date   09 / 07 / 2022
 */

#ifndef LIB_TFELMATERIAL_CHEMICALREACTION5D_BEHAVIOUR_DATA_HXX
#define LIB_TFELMATERIAL_CHEMICALREACTION5D_BEHAVIOUR_DATA_HXX

#include<limits>
#include<string>
#include<sstream>
#include<iostream>
#include<stdexcept>
#include<algorithm>

#include"TFEL/Raise.hxx"
#include"TFEL/PhysicalConstants.hxx"
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Config/TFELTypes.hxx"
#include"TFEL/TypeTraits/IsFundamentalNumericType.hxx"
#include"TFEL/TypeTraits/IsReal.hxx"
#include"TFEL/Math/General/Abs.hxx"
#include"TFEL/Math/General/IEEE754.hxx"
#include"TFEL/Math/Array/ViewsArrayIO.hxx"
#include"TFEL/Math/Array/fsarrayIO.hxx"
#include"TFEL/Math/Array/runtime_arrayIO.hxx"
#include"TFEL/Math/fsarray.hxx"
#include"TFEL/Math/runtime_array.hxx"
#include"TFEL/Math/qt.hxx"
#include"TFEL/Math/Quantity/qtIO.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/Matrix/tmatrixIO.hxx"
#include"TFEL/Math/ST2toST2/ConvertToTangentModuli.hxx"
#include"TFEL/Math/ST2toST2/ConvertSpatialModuliToKirchhoffJaumanRateModuli.hxx"
#include"TFEL/Material/FiniteStrainBehaviourTangentOperator.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"

#include "MFront/GenericBehaviour/State.hxx"
#include "MFront/GenericBehaviour/BehaviourData.hxx"
namespace tfel::material{

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename,bool>
class ChemicalReaction5dBehaviourData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis, typename NumericType,bool use_qt>
class ChemicalReaction5dIntegrationData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis, typename NumericType, bool use_qt>
std::ostream&
 operator <<(std::ostream&,const ChemicalReaction5dBehaviourData<hypothesis, NumericType, use_qt>&);

template<ModellingHypothesis::Hypothesis hypothesis,typename NumericType,bool use_qt>
class ChemicalReaction5dBehaviourData
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
static_assert(N==1||N==2||N==3);
static_assert(tfel::typetraits::IsFundamentalNumericType<NumericType>::cond);
static_assert(tfel::typetraits::IsReal<NumericType>::cond);

friend std::ostream& operator<< <>(std::ostream&,const ChemicalReaction5dBehaviourData&);

/* integration data is declared friend to access   driving variables at the beginning of the time step */
friend class ChemicalReaction5dIntegrationData<hypothesis, NumericType, use_qt>;

static constexpr unsigned short TVectorSize = N;
using StensorDimeToSize = tfel::math::StensorDimeToSize<N>;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
using TensorDimeToSize = tfel::math::TensorDimeToSize<N>;
static constexpr unsigned short TensorSize = TensorDimeToSize::value;

using ushort =  unsigned short;
using Types = tfel::config::Types<N, NumericType, use_qt>;
using Type = NumericType;
using numeric_type = typename Types::numeric_type;
using real = typename Types::real;
using time = typename Types::time;
using length = typename Types::length;
using frequency = typename Types::frequency;
using speed = typename Types::speed;
using stress = typename Types::stress;
using strain = typename Types::strain;
using strainrate = typename Types::strainrate;
using stressrate = typename Types::stressrate;
using temperature = typename Types::temperature;
using thermalexpansion = typename Types::thermalexpansion;
using thermalconductivity = typename Types::thermalconductivity;
using massdensity = typename Types::massdensity;
using energydensity = typename Types::energydensity;
using TVector = typename Types::TVector;
using DisplacementTVector = typename Types::DisplacementTVector;
using ForceTVector = typename Types::ForceTVector;
using HeatFlux = typename Types::HeatFlux;
using TemperatureGradient = typename Types::TemperatureGradient;
using Stensor = typename Types::Stensor;
using StressStensor = typename Types::StressStensor;
using StressRateStensor = typename Types::StressRateStensor;
using StrainStensor = typename Types::StrainStensor;
using StrainRateStensor = typename Types::StrainRateStensor;
using FrequencyStensor = typename Types::FrequencyStensor;
using Tensor = typename Types::Tensor;
using DeformationGradientTensor = typename Types::DeformationGradientTensor;
using DeformationGradientRateTensor = typename Types::DeformationGradientRateTensor;
using StressTensor = typename Types::StressTensor;
using StiffnessTensor = typename Types::StiffnessTensor;
using Stensor4 = typename Types::Stensor4;
using TangentOperator = tfel::math::tvector<(1)*(1)+(1)*(1),real>;
using PhysicalConstants = tfel::PhysicalConstants<NumericType, use_qt>;

protected:


#line 9 "/home/th202608/Documents/Books/MFrontBook/examples/models/ChemicalReaction5d.mfront"
tfel::math::quantity<numeric_type,0,0,0,0,0,0,1> ca;
#line 12 "/home/th202608/Documents/Books/MFrontBook/examples/models/ChemicalReaction5d.mfront"
tfel::math::quantity<numeric_type,0,0,0,0,0,0,1> cb;
temperature T;

public:

/*!
* \brief Default constructor
*/
ChemicalReaction5dBehaviourData()
{}

/*!
* \brief copy constructor
*/
ChemicalReaction5dBehaviourData(const ChemicalReaction5dBehaviourData& src)
: ca(src.ca),
cb(src.cb),
T(src.T)
{}

/*
 * \brief constructor for the Generic interface
 * \param[in] mgb_d: behaviour data
 */
ChemicalReaction5dBehaviourData(const mfront::gb::BehaviourData& mgb_d)
: ca(mgb_d.s0.internal_state_variables[0]),
cb(mgb_d.s0.internal_state_variables[1]),
T(mgb_d.s0.external_state_variables[0])
{
}


/*
* \brief Assignement operator
*/
ChemicalReaction5dBehaviourData&
operator=(const ChemicalReaction5dBehaviourData& src){
this->ca = src.ca;
this->cb = src.cb;
this->T = src.T;
return *this;
}

void exportStateData(mfront::gb::State& mbg_s1) const
{
using namespace tfel::math;
mbg_s1.internal_state_variables[0] = tfel::math::base_type_cast(this->ca);
mbg_s1.internal_state_variables[1] = tfel::math::base_type_cast(this->cb);
} // end of exportStateData

}; // end of ChemicalReaction5dBehaviourDataclass

template<ModellingHypothesis::Hypothesis hypothesis,typename NumericType, bool use_qt>
std::ostream&
operator <<(std::ostream& os,const ChemicalReaction5dBehaviourData<hypothesis, NumericType, use_qt>& b)
{
os << "ca : " << b.ca << '\n';
os << "cb : " << b.cb << '\n';
os << "T : " << b.T << '\n';
return os;
}

} // end of namespace tfel::material

#endif /* LIB_TFELMATERIAL_CHEMICALREACTION5D_BEHAVIOUR_DATA_HXX */
