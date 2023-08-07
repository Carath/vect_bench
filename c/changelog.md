# Changelog


## v1.3

Added the ``` VECT_BOUND_CHECKS ``` and ``` VECT_NULL_CHECKS ``` settings to enable bound and NULL checks during the runtime, at the cost of a performance penalty.


## v1.2

Added the ``` VECT_SHRINK_CAPACITY ``` setting to disable the automatic memory shrinking upon element removal.


## v1.1

Changed the default ``` VECT_INIT_CAPACITY ``` setting to not initially allocate a vector's array when using *vect_createEmpty()*.


## v1.0

Initial version.
