//
// Created by bernardo on 1/13/17.
//

#include <cmath>
#include "Catchment.h"
#include "../Utils/Constants.h"


Catchment::Catchment(vector<vector<double>> *streamflows_all, int series_length) : streamflows_all(streamflows_all),
                                                                                   series_length(series_length) {

    if (series_length < Constants::WEEKS_IN_YEAR * Constants::NUMBER_REALIZATIONS_ROF)
        throw std::length_error("Series shorter than required for ROF calculations. The streamflow series"
                                        "must be greater the number of ROF realizations times the number"
                                        "of weeks in a year (52).");
}

/**
 * Copy constructor.
 * @param catchment
 */
Catchment::Catchment(Catchment &catchment) : series_length(catchment.series_length),
                                             streamflows_all(catchment.streamflows_all),
                                             streamflows_realization(catchment.streamflows_realization) {
}

/**
 * Copy assignment operator.
 * @param catchment
 * @return
 */
Catchment &Catchment::operator=(const Catchment &catchment) {

    streamflows_all = catchment.streamflows_all;
    series_length = catchment.series_length;
    streamflows_realization = catchment.streamflows_realization;

    return *this;
}

/**
 * Destructor.
 */
Catchment::~Catchment() {
    if (streamflows_realization)
        delete[] streamflows_realization;
}

/**
 * Get streamflow for a given week. This function assures that the number of past inflows used for ROF
 * calculations are reserved in the beginning of the time series for ROF calculations.
 * @param week
 * @return
 */
double Catchment::getStreamflow(int week) {
    return streamflows_realization[week +
                                   (int) std::round(Constants::WEEKS_IN_YEAR * Constants::NUMBER_REALIZATIONS_ROF)];
}

/**
 * Get time series corresponding to realization index and eliminate reference to comprehensive streamflow
 * data set.
 * @param r
 */
void Catchment::setRealization(unsigned long r) {
    streamflows_realization = new double[streamflows_all->at(r).size()];
    std::copy(streamflows_all->at(r).begin(), streamflows_all->at(r).end(), streamflows_realization);
//    streamflows_all = NULL; //FIXME: FIND A WAY TO DELETE THE POINTER WITHIN THE CATCHMENT OBJECT WITHOUT DELETING IT FOR OTHER CATCHMENTS THAT POINT TO THE SAME DATA.
}

