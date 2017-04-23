# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # All Vagrant configuration is done here. The most common configuration
  # options are documented and commented below. For a complete reference,
  # please see the online documentation at vagrantup.com.

  # Every Vagrant virtual environment requires a box to build off of.
  config.vm.box = "boxcutter/ubuntu1604-desktop"

  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.memory = 2048
    vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    vb.customize ["modifyvm", :id, "--accelerate3d", "on", "--accelerate2dvideo", "on"]

  end

  config.vm.provision "shell", inline: <<-SHELL
    apt-get update -q
    apt-get install -qy software-properties-common
    apt-mark hold grub* libreoffice*
    add-apt-repository -y ppa:beineri/opt-qt58-xenial
    add-apt-repository -y ppa:ubuntu-toolchain-r/test
    apt-get update -q
    apt-get dist-upgrade -qy
    apt-get install -qy \
      bluetooth \
      bluez \
      build-essential \
      cmake \
      cmake-extras \
      extra-cmake-modules \
      freeglut* \
      git \
      libbluetooth* \
      libboost-all-dev \
      libgl{,u}1-mesa-dev \
      libsdl*1.2* \
      libx11-xcb-dev \
      libxcb-keysyms1-dev \
      libxcb-xtest0-dev \
      linux-headers-$(uname -r) \
      mesa-common-dev \
      qt583d \
      qt58base \
      qt58canvas3d \
      qt58creator \
      qt58declarative \
      qt58imageformats \
      qt58qbs \
      qt58quickcontrols \
      qt58quickcontrols2 \
      qt58script \
      qt58sensors \
      qt58svg \
      qt58tools \
      qt58x11extras \
      upx-ucl \
      virtualbox-guest-dkms \
      virtualbox-guest-utils \
      xvfb \

    cd /vagrant/wiiuse
    git clean -xdf
    cmake . -DCMAKE_BUILD_TYPE=Release
    make install

    cd /vagrant/grt/build
    git clean -xdf
    cmake . -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=False
    make install

    echo "/opt/qt58/bin/qt58-env.sh" >> /etc/profile
    echo "/opt/qt58/bin/qt58-env.sh" >> ~/.profile
  SHELL
end