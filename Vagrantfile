# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant::Config.run do |config|
  # All Vagrant configuration is done here. The most common configuration
  # options are documented and commented below. For a complete reference,
  # please see the online documentation at vagrantup.com.

  # Every Vagrant virtual environment requires a box to build off of.
  config.vm.box = "ubuntu/xenial64"

  # Boot with a GUI so you can see the screen. (Default is headless)
  config.vm.boot_mode = :gui

  # Set RAM to 2 GB
  config.vm.customize ["modifyvm", :id, "--memory", 2048]

  # Provision with a shell script
  config.vm.provider "virtualbox" do |vb|
    vb.gui = false
    vb.memory = 2048
    vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
  end

  config.vm.provision "shell", inline: <<-SHELL
    apt-get update -q
    apt-get install -qy software-properties-common
    apt-mark hold grub*
    add-apt-repository -y ppa:beineri/opt-qt58-xenial
    apt-get update -q
    apt-get dist-upgrade -qy
    apt-get install -qy \
      bluetooth \
      bluez \
      cmake \
      cmake-extras \
      extra-cmake-modules \
      g++ \
      git \
      freeglut* \
      libboost-all-dev \
      libbluetooth* \
      libsdl* \
      libgl{,u}1-mesa-dev \
      mesa-common-dev \
      qt58* \
      upx-ucl \
      xvfb \
  SHELL
end