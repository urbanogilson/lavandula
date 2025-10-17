#include "../lavandula/include/lavandula.h"

#include "controllers/controllers.h"
#include "middleware/middleware.h"

void registerRoutes(App *app) {
    Route registerUserRoute = get(app, "/api/register", registerUser);
    useLocalMiddleware(&registerUserRoute, registerUserValidator);

    Route loginUserRoute = post(app, "/api/login", loginUser);
    useLocalMiddleware(&loginUserRoute, loginUserValidator);

    Route logoutUserRoute = post(app, "/api/logout", logoutUser);
    useLocalMiddleware(&logoutUserRoute, logoutUserValidator);

    get(app, "/api/getFoodBanks", getFoodBanks);
    get(app, "/api/getFoodBank", getFoodBank);
    patch(app, "/api/updateFoodBank", updateFoodBank);
    delete(app, "/api/deleteFoodBank", deleteFoodBank);
    post(app, "/api/createFoodBank", createFoodBank);

    get(app, "/api/getDonations", getDonations);
    get(app, "/api/getDonation", getDonation);
    post(app, "/api/createDonation", createDonation);
    delete(app, "/api/deleteDonation", deleteDonation);

    get(app, "/api/getFoodBankNeeds", getFoodBankNeeds);
    post(app, "/api/createFoodBankNeed", createFoodBankNeed);
    patch(app, "/api/updateFoodBankNeed", updateFoodBankNeed);
    delete(app, "/api/deleteFoodBankNeed", deleteFoodBankNeed);
}