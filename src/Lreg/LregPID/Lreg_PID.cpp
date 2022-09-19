#ifdef UsingLib_PID

    #include <Lreg\LregPID\Lreg_PID.h>

    /*!
    *   @brief Régulation PID
        @param kp Coeff. Proportionnel
        @param ki Coeff. Intégrateur
        @param kd Coeff. Dérivateur
        @param pOn Mode de kp (P_ON_E : gain sur l'erreur | P_ON_M : gain sur la mesure)
        @param dir Sens de régulation
    */
    Lreg_PID::Lreg_PID(double _Kp, double _Ki , double _Kd, int _POn, int _ControllerDirection) :
        PID(&input, &output, &setpoint, _Kp, _Ki, _Kd, _POn, _ControllerDirection)
        {}

    /*!
    *   @brief Régulation PID
        @param kp Coeff. Proportionnel
        @param ki Coeff. Intégrateur
        @param kd Coeff. Dérivateur
        @param dir Sens de régulation
    */
    Lreg_PID::Lreg_PID(double _Kp, double _Ki, double _Kd, int _ControllerDirection) :
        PID(&input, &output, &setpoint, _Kp, _Ki, _Kd, _ControllerDirection)
        {}
#endif