#include <map>
#include <string>
#include <vector>

namespace LightTransfer
{
  class Status
  {
  public:
    int code;
    std::string message;
    Status(int _code, std::string _message) : code(_code), message(_message){};
  };

  enum class StatusCode
  {
    Continue,
    Switching_protocols,
    Processing,
    Early_Hints,
    OK,
    Created,
    Accepted,
    Non_Authoritative_Information,
    No_Content,
    Reset_Content,
    Partial_Content,
    Multi_Status,
    Already_Reported,
    IM_Used,
    Multiple_Choices,
    Moved_Permanently,
    Found,
    See_Other,
    Not_Modified,
    Use_Proxy,
    Switch_Proxy,
    Temporary_Redirect,
    Permanent_Redirect,
    Bad_Request,
    Unauthorized,
    Payment_Required,
    Forbidden,
    Not_Found,
    Method_Not_Allowed,
    Not_Acceptable,
    Proxy_Authentication_Required,
    Request_Timeout,
    Conflict,
    Gone,
    Length_Required,
    Precondition_Failed,
    Payload_Too_Large,
    URI_Too_Long,
    Unsupported_Media_Type,
    Range_Not_Satisfiable,
    Expectation_Failed,
    I_am_a_Teapot,
    Misdirected_Request,
    Unprocessable_Entity,
    Locked,
    Failed_Dependency,
    Too_Early,
    Upgrade_Required,
    Precondition_Required,
    Too_Many_Requests,
    Request_Header_Fields_Too_Large,
    Unavailable_For_Legal_Reasons,
    Internal_Server_Error,
    Not_Implemented,
    Bad_Gateway,
    Service_Unavailable,
    Gateway_Timeout,
    HTTP_Version_Not_Supported,
    Variant_Also_Negotiates,
    Insufficient_Storage,
    Loop_Detected,
    Not_Extended,
    Network_Authentication_Required,
    Unknown
  };

  const std::map<Lcdd::StatusCode, Lcdd::Status> StatusCodeMap =
      {
          {StatusCode::Continue, Status(100, "Continue")},
          {StatusCode::Switching_protocols, Status(101, "Switching protocols")},
          {StatusCode::Processing, Status(102, "Processing")},
          {StatusCode::Early_Hints, Status(103, "Early hints")},
          {StatusCode::OK, Status(200, "Ok")},
          {StatusCode::Created, Status(201, "Created")},
          {StatusCode::Accepted, Status(202, "Accepted")},
          {StatusCode::Non_Authoritative_Information, Status(203, "Non authoritative information")},
          {StatusCode::No_Content, Status(204, "No content")},
          {StatusCode::Reset_Content, Status(205, "Reset content")},
          {StatusCode::Partial_Content, Status(206, "Partial content")},
          {StatusCode::Multi_Status, Status(207, "Multi-status")},
          {StatusCode::Already_Reported, Status(208, "Already reported")},
          {StatusCode::IM_Used, Status(226, "Im used")},
          {StatusCode::Multiple_Choices, Status(300, "Multiple choices")},
          {StatusCode::Moved_Permanently, Status(301, "Moved permanently")},
          {StatusCode::Found, Status(302, "Found")},
          {StatusCode::See_Other, Status(303, "See other")},
          {StatusCode::Not_Modified, Status(304, "Not modified")},
          {StatusCode::Use_Proxy, Status(305, "Use proxy")},
          {StatusCode::Switch_Proxy, Status(306, "Switch proxy")},
          {StatusCode::Temporary_Redirect, Status(307, "Temporary redirect")},
          {StatusCode::Permanent_Redirect, Status(308, "Permanent redirect ")},
          {StatusCode::Bad_Request, Status(400, "Bad request")},
          {StatusCode::Unauthorized, Status(401, "Unauthorized")},
          {StatusCode::Payment_Required, Status(402, "Payment required")},
          {StatusCode::Forbidden, Status(403, "Forbidden")},
          {StatusCode::Not_Found, Status(404, "Not found")},
          {StatusCode::Method_Not_Allowed, Status(405, "Method not allowed")},
          {StatusCode::Not_Acceptable, Status(406, "Not acceptable")},
          {StatusCode::Proxy_Authentication_Required, Status(407, "Proxy authentication required")},
          {StatusCode::Request_Timeout, Status(408, "Request timeout")},
          {StatusCode::Conflict, Status(409, "Conflict")},
          {StatusCode::Gone, Status(410, "Gone")},
          {StatusCode::Length_Required, Status(411, "Length required")},
          {StatusCode::Precondition_Failed, Status(412, "Precondition failed")},
          {StatusCode::Payload_Too_Large, Status(413, "Payload too large")},
          {StatusCode::URI_Too_Long, Status(414, "Uri too long")},
          {StatusCode::Unsupported_Media_Type, Status(415, "Unsupported media type")},
          {StatusCode::Range_Not_Satisfiable, Status(416, "Range not satisfiable")},
          {StatusCode::Expectation_Failed, Status(417, "Expectation failed")},
          {StatusCode::I_am_a_Teapot, Status(418, "I'm a teapot")},
          {StatusCode::Misdirected_Request, Status(421, "Misdirected request")},
          {StatusCode::Unprocessable_Entity, Status(422, "Unprocessable entity")},
          {StatusCode::Locked, Status(423, "Locked")},
          {StatusCode::Failed_Dependency, Status(424, "Failed dependency")},
          {StatusCode::Too_Early, Status(425, "Too early")},
          {StatusCode::Upgrade_Required, Status(426, "Upgrade required")},
          {StatusCode::Precondition_Required, Status(428, "Precondition required")},
          {StatusCode::Too_Many_Requests, Status(429, "Too many requests")},
          {StatusCode::Request_Header_Fields_Too_Large, Status(431, "Request header fields too large")},
          {StatusCode::Unavailable_For_Legal_Reasons, Status(451, "Unavailable for legal reasons")},
          {StatusCode::Internal_Server_Error, Status(500, "Internal server error")},
          {StatusCode::Not_Implemented, Status(501, "Not implemented")},
          {StatusCode::Bad_Gateway, Status(502, "Bad gateway")},
          {StatusCode::Service_Unavailable, Status(503, "Service unavailable")},
          {StatusCode::Gateway_Timeout, Status(504, "Gateway timeout")},
          {StatusCode::HTTP_Version_Not_Supported, Status(505, "Http version not supported")},
          {StatusCode::Variant_Also_Negotiates, Status(506, "Variant also negotiates")},
          {StatusCode::Insufficient_Storage, Status(507, "Insufficient storage")},
          {StatusCode::Loop_Detected, Status(508, "Loop detected")},
          {StatusCode::Not_Extended, Status(510, "Not extended")},
          {StatusCode::Network_Authentication_Required, Status(511, "Network authentication required")},
          {StatusCode::Unknown, Status(0, "Unknown")}};

  std::string StatusCodeToFulString(Lcdd::StatusCode statusCode)
  {
    auto res = StatusCodeMap.find(statusCode);

    if (res != StatusCodeMap.end())
    {
      std::string o = std::to_string(res->second.code);

      o.append(" ");
      o.append(res->second.message);
      return o;
    }

    return "0 Unknown";
  }

  std::string StatusCodeToString(Lcdd::StatusCode statusCode)
  {
    auto res = StatusCodeMap.find(statusCode);

    if (res != StatusCodeMap.end())
    {
      return res->second.message;
    }

    return "Unknown";
  }

  int StatusCodeToInt(Lcdd::StatusCode statusCode)
  {
    auto res = StatusCodeMap.find(statusCode);

    if (res != StatusCodeMap.end())
    {
      return res->second.code;
    }

    return 0;
  }
}
