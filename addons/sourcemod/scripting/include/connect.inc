#if defined _Connect_Included
 #endinput
#endif
#define _Connect_Included

/**
 * Connection response values for OnClientPreConnectEx
 */
enum EConnect
{
	k_OnClientPreConnectEx_Reject = 0,    // Reject the connection
	k_OnClientPreConnectEx_Accept = 1,    // Accept the connection
	k_OnClientPreConnectEx_Async = -1     // Handle the connection asynchronously
};

/**
 * Steam authentication session response codes
 */
enum EAuthSessionResponse
{
	k_EAuthSessionResponseOK = 0,                             // Steam has verified the user is online, the ticket is valid and ticket has not been reused
	k_EAuthSessionResponseUserNotConnectedToSteam = 1,        // The user in question is not connected to Steam
	k_EAuthSessionResponseNoLicenseOrExpired = 2,            // The license has expired or user doesn't have license for this App ID
	k_EAuthSessionResponseVACBanned = 3,                     // The user is VAC banned for this game
	k_EAuthSessionResponseLoggedInElseWhere = 4,             // The user account has logged in elsewhere 
	k_EAuthSessionResponseVACCheckTimedOut = 5,              // VAC has been unable to perform anti-cheat checks on this user
	k_EAuthSessionResponseAuthTicketCanceled = 6,            // The ticket has been canceled by the issuer
	k_EAuthSessionResponseAuthTicketInvalidAlreadyUsed = 7,  // This ticket has already been used
	k_EAuthSessionResponseAuthTicketInvalid = 8,             // This ticket is not from a user instance currently connected to Steam
	k_EAuthSessionResponsePublisherIssuedBan = 9,            // The user is banned for this game via web API
};

/**
 * Called when a client attempts to connect to the server.
 *
 * @param sName            Client's name
 * @param sPassword        Client's password (modifiable)
 * @param sIP             Client's IP address
 * @param sSteam32ID      Client's SteamID in STEAM_X:Y:Z format
 * @param sRejectReason   Buffer to store rejection reason if connection is rejected
 * @return                Connection response (EConnect value)
 */
forward EConnect OnClientPreConnectEx(const char[] sName, char sPassword[255], const char[] sIP, const char[] sSteam32ID, char sRejectReason[255]);

/**
 * Called when Steam responds to an auth ticket validation request.
 *
 * @param eAuthSessionResponse         The response code from Steam
 * @param bGotValidateAuthTicketResponse  Whether a response was received
 * @param bSteamLegal                 Whether the authentication was legal
 * @param sSteam32ID                  Client's SteamID in STEAM_X:Y:Z format
 */
forward void OnValidateAuthTicketResponse(EAuthSessionResponse eAuthSessionResponse, bool bGotValidateAuthTicketResponse, bool bSteamLegal, char sSteam32ID[32]);

/**
 * Responds to a pending client connection request.
 *
 * @param sSteam32ID      Client's SteamID in STEAM_X:Y:Z format
 * @param RetVal          Connection response (EConnect value)
 * @param sRejectReason   Reason for rejection if RetVal is k_OnClientPreConnectEx_Reject
 * @return                True if successful, false otherwise
 */
native bool ClientPreConnectEx(const char[] sSteam32ID, EConnect RetVal, char sRejectReason[255]);

/**
 * Checks if a client has been authenticated by Steam.
 *
 * @param sSteam32ID      Client's SteamID in STEAM_X:Y:Z format
 * @return                True if authenticated, false otherwise
 */
native bool SteamClientAuthenticated(const char[] sSteam32ID);

/**
 * Checks if a response was received from Steam for this client's auth ticket.
 *
 * @param sSteam32ID      Client's SteamID in STEAM_X:Y:Z format
 * @return                True if response received, false otherwise
 */
native bool SteamClientGotValidateAuthTicketResponse(const char[] sSteam32ID);

/**
 * Do not edit below this line!
 */
public Extension __ext_connect =
{
	name = "Connect",
	file = "connect.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

#if !defined REQUIRE_EXTENSIONS
public void __ext_connect_SetNTVOptional()
{
	MarkNativeAsOptional("ClientPreConnectEx");
	MarkNativeAsOptional("SteamClientAuthenticated");
	MarkNativeAsOptional("SteamClientGotValidateAuthTicketResponse");
}
#endif
