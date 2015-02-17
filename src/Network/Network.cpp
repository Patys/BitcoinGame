#include <Network.h>
#include <string>

void sendScore(int score, const std::string& name, int time_played)
{
    // prepare the request
    sf::Http::Request request("/post_score", sf::Http::Request::Post);

    // encode the parameters in the request body
    std::ostringstream stream;
    stream << score;

    std::ostringstream stream_time;
    stream_time << time_played;

    request.setBody("name=" + name + "&score=" + stream.str());

    // send the request
    sf::Http http("http://bitcoin-patys.rhcloud.com");
    sf::Http::Response response = http.sendRequest(request);
    
    // check the status
    if (response.getStatus() == sf::Http::Response::Ok)
    {
        // check the contents of the response
        std::cout << response.getBody() << std::endl;
    }
    else
    {
      std::cout << "request failed: " << response.getStatus() << "\n" << response.getBody() << std::endl;
    }
}
