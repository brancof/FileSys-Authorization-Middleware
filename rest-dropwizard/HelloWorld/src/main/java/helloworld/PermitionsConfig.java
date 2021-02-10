package helloworld;

import io.dropwizard.Configuration;
import javax.validation.constraints.NotEmpty;

public class PermitionsConfig extends Configuration {
    @NotEmpty
    public String template;

    @NotEmpty
    public String defaultName = "Stranger";
}
