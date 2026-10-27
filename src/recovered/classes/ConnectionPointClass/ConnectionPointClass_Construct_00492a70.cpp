ConnectionPointClass::ConnectionPointClass(GUID const &iid,IUnknown *container):InterfaceID(iid),RefCount(0),Container(container),Connections() { container->AddRef(); }
