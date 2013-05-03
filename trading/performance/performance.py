# -*- coding: utf-8 -*-

# Author: Michael Halls-Moore - QuantStart.com
# Created: 30th April 2013

"""
Function library for calculating performance of trading 
strategies.

Makes use of the pandas library in order to eliminate most
of the headaches associated with Python data analysis.

Provides functions for the Sharpe Ratio, Drawdowns.
"""

import numpy as np


def sharpe_ratio(profit_loss, period='Y', freq='D'):
    """
    Calculate the Sharpe Ratio of a profit & loss series.

    The Sharpe Ratio characterises the reward-to-risk ratio
    of the strategy. A higher Sharpe means greater return per
    unit of risk (with 'risk' defined as standard deviation).
    
    To 'annualise' the Sharpe Ratio, 250 data points are
    used. However, other periods are supported for higher
    frequency strategies.
    """
    return np.sqrt(250) * profit_loss.mean() / profit_loss.std()

