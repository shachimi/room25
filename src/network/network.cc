#include "network/network.hh"

Network *Network::instance = NULL;

Network::Network(void)
{
}

Network::~Network(void)
{
}

Network *getInstance(void)
{
    if (!this->instance) {
        this->instance = new Network();
    }

    return this->instance;
}

int Network::wait(net_req_t req_type)
{
}

int Network::forward(Scheduling *scheduling)
{
}

int Network::bcast(Scheduling *scheduling)
{
}
