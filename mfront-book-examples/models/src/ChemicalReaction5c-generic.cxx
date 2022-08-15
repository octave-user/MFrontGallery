/*!
* \file   ChemicalReaction5c-generic.cxx
* \brief  This file implements the umat interface for the ChemicalReaction5c behaviour law
* \author Thomas Helfer
* \date   09 / 07 / 2022
*/

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif /* NOMINMAX */
#include <windows.h>
#ifdef small
#undef small
#endif /* small */
#endif /* _WIN32 */

#ifndef MFRONT_SHAREDOBJ
#define MFRONT_SHAREDOBJ TFEL_VISIBILITY_EXPORT
#endif /* MFRONT_SHAREDOBJ */

#ifndef MFRONT_EXPORT_SYMBOL
#define MFRONT_EXPORT_SYMBOL(TYPE, NAME, VALUE) \
  MFRONT_SHAREDOBJ extern TYPE NAME;            \
  MFRONT_SHAREDOBJ TYPE NAME = VALUE
#endif /* MFRONT_EXPORT_SYMBOL*/

#ifndef MFRONT_EXPORT_ARRAY_ARGUMENTS
#define MFRONT_EXPORT_ARRAY_ARGUMENTS(...) __VA_ARGS__
#endif /* MFRONT_EXPORT_ARRAY_ARGUMENTS */

#ifndef MFRONT_EXPORT_ARRAY_OF_SYMBOLS
#define MFRONT_EXPORT_ARRAY_OF_SYMBOLS(TYPE, NAME, SIZE, VALUE) \
  MFRONT_SHAREDOBJ extern TYPE NAME[SIZE];                      \
  MFRONT_SHAREDOBJ TYPE NAME[SIZE] = {VALUE}
#endif /* MFRONT_EXPORT_ARRAY_OF_SYMBOLS*/

#include<iostream>
#include<cstdlib>
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Math/t2tot2.hxx"
#include"TFEL/Math/t2tost2.hxx"
#include"TFEL/Material/ChemicalReaction5c.hxx"
#include"MFront/GenericBehaviour/GenericBehaviourTraits.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"
#include"MFront/GenericBehaviour/ChemicalReaction5c-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
ChemicalReaction5c_getOutOfBoundsPolicy(){
static auto policy = tfel::material::None;
return policy;
}

namespace mfront::gb{

template<>
struct GenericBehaviourTraits<tfel::material::ChemicalReaction5c<tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN, real, true>>{
static constexpr auto hypothesis = tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
static constexpr auto N = tfel::material::ModellingHypothesisToSpaceDimension<hypothesis>::value;
static constexpr auto StensorSize = tfel::material::ModellingHypothesisToStensorSize<hypothesis>::value;
static constexpr auto TensorSize = tfel::material::ModellingHypothesisToTensorSize<hypothesis>::value;
};

template<>
struct GenericBehaviourTraits<tfel::material::ChemicalReaction5c<tfel::material::ModellingHypothesis::AXISYMMETRICAL, real, true>>{
static constexpr auto hypothesis = tfel::material::ModellingHypothesis::AXISYMMETRICAL;
static constexpr auto N = tfel::material::ModellingHypothesisToSpaceDimension<hypothesis>::value;
static constexpr auto StensorSize = tfel::material::ModellingHypothesisToStensorSize<hypothesis>::value;
static constexpr auto TensorSize = tfel::material::ModellingHypothesisToTensorSize<hypothesis>::value;
};

template<>
struct GenericBehaviourTraits<tfel::material::ChemicalReaction5c<tfel::material::ModellingHypothesis::PLANESTRAIN, real, true>>{
static constexpr auto hypothesis = tfel::material::ModellingHypothesis::PLANESTRAIN;
static constexpr auto N = tfel::material::ModellingHypothesisToSpaceDimension<hypothesis>::value;
static constexpr auto StensorSize = tfel::material::ModellingHypothesisToStensorSize<hypothesis>::value;
static constexpr auto TensorSize = tfel::material::ModellingHypothesisToTensorSize<hypothesis>::value;
};

template<>
struct GenericBehaviourTraits<tfel::material::ChemicalReaction5c<tfel::material::ModellingHypothesis::GENERALISEDPLANESTRAIN, real, true>>{
static constexpr auto hypothesis = tfel::material::ModellingHypothesis::GENERALISEDPLANESTRAIN;
static constexpr auto N = tfel::material::ModellingHypothesisToSpaceDimension<hypothesis>::value;
static constexpr auto StensorSize = tfel::material::ModellingHypothesisToStensorSize<hypothesis>::value;
static constexpr auto TensorSize = tfel::material::ModellingHypothesisToTensorSize<hypothesis>::value;
};

template<>
struct GenericBehaviourTraits<tfel::material::ChemicalReaction5c<tfel::material::ModellingHypothesis::TRIDIMENSIONAL, real, true>>{
static constexpr auto hypothesis = tfel::material::ModellingHypothesis::TRIDIMENSIONAL;
static constexpr auto N = tfel::material::ModellingHypothesisToSpaceDimension<hypothesis>::value;
static constexpr auto StensorSize = tfel::material::ModellingHypothesisToStensorSize<hypothesis>::value;
static constexpr auto TensorSize = tfel::material::ModellingHypothesisToTensorSize<hypothesis>::value;
};

} // end of namespace mfront::gb

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_author, "Thomas Helfer");

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_date, "09 / 07 / 2022");

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_description, "");

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_build_id, "");

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_mfront_ept, "ChemicalReaction5c");

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_tfel_version, "4.1.0-dev");

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_mfront_mkt, 1u);

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_mfront_interface, "Generic");

MFRONT_EXPORT_SYMBOL(const char*, ChemicalReaction5c_src, "ChemicalReaction5c.mfront");

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nModellingHypotheses, 5u);

MFRONT_EXPORT_ARRAY_OF_SYMBOLS(const char *, ChemicalReaction5c_ModellingHypotheses, 5, MFRONT_EXPORT_ARRAY_ARGUMENTS("AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical","PlaneStrain","GeneralisedPlaneStrain","Tridimensional"));

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nMainVariables, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nGradients, 0u);

MFRONT_EXPORT_SYMBOL(const int *, ChemicalReaction5c_GradientsTypes, nullptr);

MFRONT_EXPORT_SYMBOL(const char * const *, ChemicalReaction5c_Gradients, nullptr);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nThermodynamicForces, 0u);

MFRONT_EXPORT_SYMBOL(const int *, ChemicalReaction5c_ThermodynamicForcesTypes, nullptr);

MFRONT_EXPORT_SYMBOL(const char * const *, ChemicalReaction5c_ThermodynamicForces, nullptr);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nTangentOperatorBlocks, 4u);

MFRONT_EXPORT_ARRAY_OF_SYMBOLS(const char *, ChemicalReaction5c_TangentOperatorBlocks, 4, MFRONT_EXPORT_ARRAY_ARGUMENTS("MolarConcentrationOfSpeciesA",
"Temperature","MolarConcentrationOfSpeciesB","Temperature"));

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_BehaviourType, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_BehaviourKinematic, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_SymmetryType, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_ElasticSymmetryType, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_api_version, 1u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_TemperatureRemovedFromExternalStateVariables, 1u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_UsableInPurelyImplicitResolution, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nMaterialProperties, 0u);

MFRONT_EXPORT_SYMBOL(const char * const *, ChemicalReaction5c_MaterialProperties, nullptr);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nInternalStateVariables, 2u);
MFRONT_EXPORT_ARRAY_OF_SYMBOLS(const char *, ChemicalReaction5c_InternalStateVariables, 2, MFRONT_EXPORT_ARRAY_ARGUMENTS("MolarConcentrationOfSpeciesA",
"MolarConcentrationOfSpeciesB"));

MFRONT_EXPORT_ARRAY_OF_SYMBOLS(int, ChemicalReaction5c_InternalStateVariablesTypes, 2, MFRONT_EXPORT_ARRAY_ARGUMENTS(0,0));

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nExternalStateVariables, 0u);
MFRONT_EXPORT_SYMBOL(const char * const *, ChemicalReaction5c_ExternalStateVariables, nullptr);

MFRONT_EXPORT_SYMBOL(const int *, ChemicalReaction5c_ExternalStateVariablesTypes, nullptr);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nParameters, 6u);

MFRONT_EXPORT_ARRAY_OF_SYMBOLS(const char *, ChemicalReaction5c_Parameters, 6, MFRONT_EXPORT_ARRAY_ARGUMENTS("ReferenceReactionRateCoefficientAB",
"ReferenceReactionRateCoefficientBA","ActivationTemperatureAB","ActivationTemperatureBA","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor"));

MFRONT_EXPORT_ARRAY_OF_SYMBOLS(int, ChemicalReaction5c_ParametersTypes, 6, MFRONT_EXPORT_ARRAY_ARGUMENTS(0,0,0,0,0,0));

MFRONT_EXPORT_SYMBOL(double, ChemicalReaction5c_ReferenceReactionRateCoefficientAB_ParameterDefaultValue, 0.01837750538756);

MFRONT_EXPORT_SYMBOL(double, ChemicalReaction5c_ReferenceReactionRateCoefficientBA_ParameterDefaultValue, 0.010131981128094);

MFRONT_EXPORT_SYMBOL(double, ChemicalReaction5c_ActivationTemperatureAB_ParameterDefaultValue, 3000);

MFRONT_EXPORT_SYMBOL(double, ChemicalReaction5c_ActivationTemperatureBA_ParameterDefaultValue, 1500);

MFRONT_EXPORT_SYMBOL(double, ChemicalReaction5c_minimal_time_step_scaling_factor_ParameterDefaultValue, 0.1);

MFRONT_EXPORT_SYMBOL(double, ChemicalReaction5c_maximal_time_step_scaling_factor_ParameterDefaultValue, 1.7976931348623e+308);

MFRONT_EXPORT_SYMBOL(long double, ChemicalReaction5c_Temperature_LowerPhysicalBound, static_cast<long double>(0));

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_requiresStiffnessTensor, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_requiresThermalExpansionCoefficientTensor, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nInitializeFunctions, 0u);

MFRONT_EXPORT_SYMBOL(const char * const *, ChemicalReaction5c_InitializeFunctions, nullptr);


MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_nPostProcessings, 0u);

MFRONT_EXPORT_SYMBOL(const char * const *, ChemicalReaction5c_PostProcessings, nullptr);


MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_ComputesInternalEnergy, 0u);

MFRONT_EXPORT_SYMBOL(unsigned short, ChemicalReaction5c_ComputesDissipatedEnergy, 0u);

MFRONT_SHAREDOBJ void
ChemicalReaction5c_setOutOfBoundsPolicy(const int p){
if(p==0){
ChemicalReaction5c_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
ChemicalReaction5c_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
ChemicalReaction5c_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "ChemicalReaction5c_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
ChemicalReaction5c_setParameter(const char *const key,const double value){
using tfel::material::ChemicalReaction5cParametersInitializer;
auto& i = ChemicalReaction5cParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int ChemicalReaction5c_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = ChemicalReaction5c<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d, Behaviour::STANDARDTANGENTOPERATOR, ChemicalReaction5c_getOutOfBoundsPolicy());
return r;
} // end of ChemicalReaction5c_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ChemicalReaction5c_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = ChemicalReaction5c<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d, Behaviour::STANDARDTANGENTOPERATOR, ChemicalReaction5c_getOutOfBoundsPolicy());
return r;
} // end of ChemicalReaction5c_Axisymmetrical

MFRONT_SHAREDOBJ int ChemicalReaction5c_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = ChemicalReaction5c<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d, Behaviour::STANDARDTANGENTOPERATOR, ChemicalReaction5c_getOutOfBoundsPolicy());
return r;
} // end of ChemicalReaction5c_PlaneStrain

MFRONT_SHAREDOBJ int ChemicalReaction5c_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = ChemicalReaction5c<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d, Behaviour::STANDARDTANGENTOPERATOR, ChemicalReaction5c_getOutOfBoundsPolicy());
return r;
} // end of ChemicalReaction5c_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ChemicalReaction5c_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = ChemicalReaction5c<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d, Behaviour::STANDARDTANGENTOPERATOR, ChemicalReaction5c_getOutOfBoundsPolicy());
return r;
} // end of ChemicalReaction5c_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

