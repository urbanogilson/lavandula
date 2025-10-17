#ifndef controllers_h
#define controllers_h

#include "../../lavandula/include/lavandula.h"

appRoute(registerUser, ctx);
appRoute(loginUser, ctx);
appRoute(logoutUser, ctx);

appRoute(getFoodBanks, ctx);
appRoute(getFoodBank, ctx);
appRoute(createFoodBank, ctx);
appRoute(updateFoodBank, ctx);
appRoute(deleteFoodBank, ctx);

appRoute(getDonations, ctx);
appRoute(getDonation, ctx);
appRoute(createDonation, ctx);
appRoute(deleteDonation, ctx);

appRoute(getFoodBankNeeds, ctx);
appRoute(createFoodBankNeed, ctx);
appRoute(updateFoodBankNeed, ctx);
appRoute(deleteFoodBankNeed, ctx);

#endif
