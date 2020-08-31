## Module stuff
package PacketCDM_P; 
use strict;
use base 'PacketCDM';
use fields qw(
    mPipelineCmd
    mTemporarilyUnparsedText
    );

use Exporter qw(import);

our @EXPORT_OK = qw();
our %EXPORT_TAGS;

## Imports
use Constants qw(:all);
use DP qw(:all);
use T2Utils qw(:all);

BEGIN { push @Packet::PACKET_CLASSES, __PACKAGE__ }

## Methods
sub new {
    my ($class) = @_;
    my $self = fields::new($class);
    $self->SUPER::new();
    $self->{mCmd} = "P";
    $self->{mPipelineCmd} = "_";
    return $self;
}

### CLASS METHOD
sub recognize {
    my ($class,$packet) = @_;
    return $class->SUPER::recognize($packet)
        && $packet =~ /^..P/;
}

##VIRTUAL
sub packFormatAndVars {
    my __PACKAGE__ $self = shift;
    my ($parentfmt,@parentvars) = $self->SUPER::packFormatAndVars();
    my ($myfmt,@myvars) =
        ("a1 a*", 
         \$self->{mPipelineCmd},
         \$self->{mTemporarilyUnparsedText}
        );

    return ($parentfmt.$myfmt,
            @parentvars, @myvars);
}

##VIRTUAL
sub validate {
    my $self = shift;
    my $ret = $self->SUPER::validate();
    return $ret if defined $ret;
    return "Bad P command '$self->{mCmd}'"
        unless $self->{mCmd} eq "P";
    return "Bad pipeline command in P packet"
        unless $self->{mPipelineCmd} =~ /[A-Z]/;
    return undef;
}

##VIRTUAL
sub handleInbound {
    my __PACKAGE__ $self = shift;
    my CDM $cdm = shift;
    my $nm = $self->getNMIfAny($cdm);
    return DPSTD("No NM for ".$self->summarize())
        unless $nm;
    return
        unless $nm->state() >= NGB_STATE_OPEN;
    return DPSTD("XXX HANDLE ".$self->summarize())
}

1;

